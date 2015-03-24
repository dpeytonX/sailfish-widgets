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

#include "query.h"
#include "sqlitedatabase.h"

#include <QSqlRecord>
#include <QSqlError>

/*!
   \class Query
   \since 5.0
   \brief The Query class

   \inmodule Database

   This class will allow you to get more information about a query performed using \l {SQLiteDatabase}.

   It is not meant to be instantiated as a QML object.

   An example usage is as follows.
   \qml
   SQLiteDatabase {
     Component.onCompleted: {
       exec("SELECT * FROM table")
       if(query.valid()) {
         query.first() // this will return the Query QML object
         console.log(query.value("column"))
       }
     }
   }
   \endqml

   Back to \l {Sailfish Widgets}

 */

/*!
 \fn Query::Query(QObject *parent)

 Sets a \c QObject \a parent.
 */
Query::Query(QObject *parent) : QObject(parent), QSqlQuery() {}

/*!
 \fn Query::Query(SQLiteDatabase* database)

 It sets the internal \c QSqlQuery 's database to be \a database and a \c QObject \c parent of \a database.
 */
Query::Query(SQLiteDatabase* database) : QObject(database), QSqlQuery(database->database()) {}

/*!
 \fn Query::Query(const QString& query, SQLiteDatabase* database)

 It sets the internal \c QSqlQuery to be \a query and a \c QObject \c parent of \a database.
 */
Query::Query(const QString& query, SQLiteDatabase* database) : QObject(database), QSqlQuery(query, database->database()) {}

/*!
  \fn bool Query::first()

  Seeks to the first record in this query. Returns true if successful.
 */
bool Query::first() {
    return QSqlQuery::first();
}

/*!
  \fn bool Query::next()

  Seeks to the next record in this query. Returns true if successful.
 */
bool Query::next() {
    return QSqlQuery::next();
}

/*!
  \fn bool Query::last()

  Seeks to the last record in this query. Returns true if successful.
 */
bool Query::last() {
    return QSqlQuery::last();
}

/*!
  \fn int Query::fieldSize()

  Returns the number of fields returned by this query.
 */
int Query::fieldSize() {
    return QSqlQuery::record().count();
}

/*!
  \fn void Query::finish()

  Releases resources and sets this query to inactive
 */
void Query::finish() {
    return QSqlQuery::finish();
}

/*!
  \fn void Query::close()

  Releases resources and sets this query to inactive. Alias to \c finish();
 */
void Query::close() {
    return finish();
}

/*!
  \fn bool Query::seek(int index, bool relative)
 Searches for the record \a index in this query and returns true if successful.

 To search relatively, set \a relative to true.
 */
bool Query::seek(int index, bool relative) {
    return QSqlQuery::seek(index, relative);
}

/*!
  \fn int Query::indexOf(const QString& field)
  Returns the index of \a field or -1 if no such field was found.
 */
int Query::indexOf(const QString& field) {
    return QSqlQuery::record().indexOf(field);
}

/*!
 \property Query::lastError
 Returns the textual description of the last error that occurred.
 */
QString Query::lastError() const {
    return QSqlQuery::lastError().text();
}

/*!
  \fn QVariant Query::value(const QString& name)
  Returns the value of the record at the column designated by \a name.
 */
QVariant Query::value(const QString& name) {
    return QSqlQuery::value(name);
}

/*!
 \property Query::active
 Returns if the query is still active (can return rows).
 */
/*!
 \property Query::size
 Returns the number of rows returned from the query.
 */
/*!
 \property Query::fieldSize
 Returns the number of fields returned from the query.
 */
/*!
 \property Query::valid
 Returns if the query is positioned at a valid record.
 */
/*!
 \property Query::lastQuery
 Is a textual representation of the query before execution.
 */
/*!
 \property Query::executedQuery
 Is a textual representation of the query after execution
 */
