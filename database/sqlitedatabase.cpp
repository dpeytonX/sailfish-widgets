/***************************************************************************
** This file is part of SailfishWidgets
**
** Copyright (c) 2014 Dametrious Peyton
**
** $QT_BEGIN_LICENSE:GPLV3$
** SailfishWidgets is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** SailfishWidgets is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with SailfishWidgets.  If not, see <http://www.gnu.org/licenses/>.
** $QT_END_LICENSE$
**
**************************************************************************/

#include "sqlitedatabase.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QStringList>
#include <QSqlError>

/*!
   \class SQLiteDatabase
   \since 5.0
   \brief The SQLiteDatabase class

   \inmodule Database

   This class will act as a QML accessible database layer.

   An example usage is as follows.
   \qml
   SQLiteDatabase {
    onValidateDatabase: {
        //Check if this is an sql lite db
        if(opened) close()

        console.debug("opening db at " + filePath)
        databaseName = filePath

        if(!open()) return false

        console.debug("running query on " + databaseName)

        //Check for a mnemosyne table for verification

        var result = exec("SELECT * FROM table WHERE key='version' AND value='1.0';")
        if(!result) {
            console.error(lastError)
            validDb = false
        }
        console.debug("query was valid")

        if(query.indexOf("value") !== -1) initTrackingValues()

        validDb = result
    }
   }
   \endqml

   Back to \l {Sailfish Widgets}

 */

/*!
  \fn void SQLiteDatabase::SQLiteDatabase(QQuickItem *parent)
  Sets the \a parent.
 */
SQLiteDatabase::SQLiteDatabase(QQuickItem *parent) : QQuickItem(parent),
  m_lastQuery(), m_query(new Query(m_lastQuery, this))
{
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setHostName("localhost");
}

/*!
  \fn QSqlDatabase& SQLiteDatabase::database()
  Returns a reference to the internal SQLite database.
 */
QSqlDatabase& SQLiteDatabase::database() {
    return m_database;
}

/*!
  \fn bool SQLiteDatabase::open()
  Opens the database. This requires that the database name be set.

  Returns true if successful.

  \sa setDatabaseName()
 */
bool SQLiteDatabase::open() {
    bool result = m_database.open();
    if(result && m_database.isOpen()) emit openedChanged();
    return result;
}

/*!
  \fn bool SQLiteDatabase::opened()
  Returns true if the database has been opened.
 */
bool SQLiteDatabase::opened() {
    return m_database.isOpen();
}

/*!
  \fn bool SQLiteDatabase::valid()
  Returns true if the database file given is a valid SQLite database.
 */
bool SQLiteDatabase::valid() {
    return m_database.isValid();
}

/*!
  \fn QString SQLiteDatabase::databaseName()
  Returns the current database name.

  \sa setDatabaseName()
 */
QString SQLiteDatabase::databaseName() {
    return m_database.databaseName();
}

/*!
  \fn void SQLiteDatabase::setDatabaseName(const QString& name)
  Sets the database name to \a name. You must do this before calling \c open().

  Emits the \c databaseNameChanged() signal

  \sa open()
 */
void SQLiteDatabase::setDatabaseName(const QString& name) {
    m_database.setDatabaseName(name);
    emit databaseNameChanged();
}

/*!
  \fn void SQLiteDatabase::close()
  Closes the database. Emits the \c openedChanged() signal.
 */
void SQLiteDatabase::close() {
    m_database.close();
    emit openedChanged();
}

/*!
  \fn bool SQLiteDatabase::transaction()
  Starts a new SQLite transaction.

  Returns true if successful.
 */
bool SQLiteDatabase::transaction() {
    return m_database.transaction();
}

/*!
  \fn bool SQLiteDatabase::rollback()
  Rolls back a database transaction.

  This method will automatically invalidate the existing query.

  Returns true if successful.
 */
bool SQLiteDatabase::rollback() {
    m_lastQuery.finish();
    return m_database.rollback();
}

/*!
  \fn bool SQLiteDatabase::commit()
  Ends an SQLite transaction. Returns true if successful.
 */
bool SQLiteDatabase::commit() {
    return m_database.commit();
}

/*!
  \fn bool SQLiteDatabase::create(QString filePath)
  Creates a new SQLiteDatabase at \a filePath and opens it.

  Returns true if the database was succesfully opened.

  \sa open()
 */
bool SQLiteDatabase::create(QString filePath) {
    if(opened()) close();

    QFileInfo info(filePath);
    QDir(info.absolutePath()).mkpath(info.absolutePath());
    QFile file(filePath);

    if(file.exists()) file.remove();
    file.open(QIODevice::WriteOnly); //touch the file
    file.close();
    m_database.setDatabaseName(filePath);
    return open();
}

/*!
  \fn bool SQLiteDatabase::execBatch(QStringList batch, bool ignoreErrors)
  Executes a \a batch of commands. Each command must be a single SQL statement, but need not to end with a semicolon.

  Each statement is executed in succession until an error occurs, unless \a ignoreErrors is true in which
  case execBatch will continue until the end.

  As a side note:
  \list
  \li Empty commands are ignored
  \li Commands of \code "begin transaction" \endcode or \code "commit" \endcode will be converted into calls to \c transaction and \c commit() , respectively.
  \endlist

  This method will return true if completed succesfully. False, otherwise.

  \sa exec(), transaction(), commit()
 */
bool SQLiteDatabase::execBatch(QStringList batch, bool ignoreErrors) {
    foreach(QString c, batch) {
        if(c.trimmed().isEmpty()) continue;

        if(!exec(c) && !ignoreErrors) {
            qDebug() << "exec batch: error occurred " << c << lastError();
            return false;
        }
    }
    return true;
}

/*!
  \fn bool SQLiteDatabase::exec(QString query)
  Executes a QString \a query.

  Returns true if successful. False otherwise.

  Using an empty query will instead invoke the last query. This is mostly useful if you previously called the \c prepare() method
  and you need to execute it after added values with \c bind().

  \sa prepare(), bind()
 */
bool SQLiteDatabase::exec(QString query) {
    query = query.trimmed();

    if(query.isEmpty())
        return m_lastQuery.exec();

    if(query.at(query.length() - 1) != ';') query.append(";");

    if(query.toLower().startsWith("begin transaction")) {
        setLastQuery(QSqlQuery(m_database));
        return m_database.transaction();
    }

    if(query.toLower().startsWith("commit")) {
        setLastQuery(QSqlQuery(m_database));
        return m_database.commit();
    }

    if(query.toLower().startsWith("rollback")) {
        setLastQuery(QSqlQuery(m_database));
        return m_database.rollback();
    }

    setLastQuery(QSqlQuery(query, m_database));
    return m_lastQuery.exec();
}

/*!
  \fn bool SQLiteDatabase::prepare(QString query)
  Prepares a boundable \a query.

  Returns true if successful.
 */
bool SQLiteDatabase::prepare(QString query) {
    setLastQuery(QSqlQuery(m_database));
    return m_lastQuery.prepare(query);
}

/*!
  \fn void SQLiteDatabase::bind(QString key, QVariant value)
  Binds the string \a key with the specified \a value to the last query.
 */
void SQLiteDatabase::bind(QString key, QVariant value) {
    m_lastQuery.bindValue(key, value);
}

/*!
  \fn QSqlQuery SQLiteDatabase::lastQuery()
  Returns the last query that was created using \c exec() or \c prepare()
 */
QSqlQuery SQLiteDatabase::lastQuery() {
    return m_lastQuery;
}

/*!
  \internal
 */
void SQLiteDatabase::setLastQuery(const QSqlQuery& query) {
    m_lastQuery = query;
    delete m_query;
    m_query = new Query(m_lastQuery, this);
    emit queryChanged();
}

/*!
  \fn QString SQLiteDatabase::lastError()
 Returns the textual description of the last error that occurred.
 */
QString SQLiteDatabase::lastError() {
    return QString(m_lastQuery.lastError().text()) + " " + m_database.lastError().text();
}

/*!
  \fn Query* SQLiteDatabase::query()
  This method will return the last \l {Query} object that was created using the \c exec() or \c prepare() methods.

  \warning \l {Query} objects will be deleted whenever you call a \c exec() or \c prepare().

  Therefore, you must not use the object returned from this method after executing a new SQL statement.
 */
Query* SQLiteDatabase::query() {
    return m_query;
}

/*!
  \fn void SQLiteDatabase::openedChanged()
  Emitted when the database's open state has changed.
  */
/*!
  \fn void SQLiteDatabase::databaseNameChanged()
  Emitted when the database name has changed.
  */
/*!
  \fn void SQLiteDatabase::queryChanged()
  Emitted when the last ran query has changed.
  */
