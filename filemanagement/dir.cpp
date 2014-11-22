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

#include "dir.h"

/*!
   \class Dir
   \since 5.0
   \brief The Dir class

   \inmodule FileManagement

   This class will expose \c QDir functionality to QML.

   An example usage is as follows.
   \qml
   Dir {
        id: fileList
        filter: Dir.AllEntries | Dir.Hidden
        sort: Dir.DirsFirst | Dir.Name

        onPathChanged: refresh()
    }
   \endqml

   It does not support file manipulation (creation, reading, writing, delete). This class may be extended in the future as needed.

   Back to \l {Sailfish Widgets}

 */

/*!
   \variable Dir::m_configDir
   Link to the XDG application configuration path.
 */
const QString Dir::m_configDir = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
/*!
   \variable Dir::m_dataDir
   Link to the XDG application data path.
 */
const QString Dir::m_dataDir = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
/*!
   \variable Dir::m_cacheDir
   Link to the XDG application cache path.
 */
const QString Dir::m_cacheDir = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
/*!
   \variable Dir::m_homeDir
   Link to the XDG user HOME path.
 */
const QString Dir::m_homeDir = QDir::homePath();

/*!
 \fn Dir::Dir(QObject *parent)
 Constructs a new \l {Dir} with the given \c QObject \a parent
 */
Dir::Dir(QObject *parent) :
    QObject(parent),
    QDir(),
    m_fileList(QQmlListProperty<File>(this, 0,
                                      &Dir::dclAppendObject,
                                      &Dir::dclCountObject,
                                      &Dir::dclAtIndex,
                                      &Dir::dclClearObject))
{

}

/*!
 \fn Dir::dirName() const

 Returns the directory name. Unlike \c QDir::dirName() it will convert the root path to \c / .
 */
QString Dir::dirName() const { return isRoot() ? root().path() : QDir::dirName(); }

/*!
 \fn Dir::entryList()
 Returns the files in this \l {Dir} object's \c Dir::path(). It provides this object's
 \c filter and \c sort properties as arguments to \c QDir::entryList().

 This applies the following \c DirFilter enums (always).

 \list
   \li \c QDir::Readable
   \li \c QDir::NoDot
 \endlist

 */
QStringList Dir::entryList() {
    return QDir::entryList(Filters(m_filter) | QDir::Readable | QDir::NoDot, SortFlags(m_sort));
}

/*!
 \fn Dir::files()
 Returns the files in this directory as \l {File} objects.

 If the internal file list is unpopulated, a call to this method will populate it.

 It will return the same content as \c entryList().

 \sa Dir::entryList()
 */
QQmlListProperty<File> Dir::files() {
    if(getList().isEmpty())
        foreach(QString s, entryList())
            getList().append(new File(absoluteFilePath(s), this));

    return m_fileList;
}

/*!
   \fn Dir::filter() const

   Returns the internal file list filter.
 */
int Dir::filter() const { return m_filter; }

/*!
 \fn Dir::refresh()

 It will clear the current list and call \c files().
 Afterwords it will emit the \c filesChanged() method.

 \sa Dir::filesChanged()
 */
void Dir::refresh() {
    clearList();
    files();
    emit filesChanged();
}

/*!
 \fn Dir::setFilter(int filter)

 It set the current \a filter.
 Afterwords it will emit the \c filterChanged() method.

 \sa Dir::filterChanged()
 */
void Dir::setFilter(int filter) {
    m_filter = filter;
    emit filterChanged();
}

/*!
 \fn Dir::setPath(const QString &p)

 It will set the current path to \a p after running QDir::absolutePath().

 To workaround an issue with indefinate /.. when navigating code, it will
 force references of /.. to the root directory.

 Afterwords it will emit the \c pathChanged() method.

 \sa Dir::pathChanged()
 */
void Dir::setPath(const QString &p) {
    QDir nPath(p);
    //Weird workaround for inifinite /../..
    QDir::setPath(nPath.path() == "/.." ? "/" : nPath.absolutePath());
    emit pathChanged();
}

/*!
 \fn Dir::setSort(int sort)

 It will set this object's \a sort method
 Afterwords it will emit the \c sortChanged() method.

 \sa Dir::sortChanged()
 */
void Dir::setSort(int sort) {
    m_sort = sort;
    emit sortChanged();
}

/*!
  \fn Dir::sort() const
  \brief Gets the current sort method.

 */
int Dir::sort() const { return m_sort; }

/*!
 \fn void Dir::pathChanged()
 Emitted when the \c path is updated.
 */

/*!
 \fn void Dir::filterChanged()
 Emitted when the \c filter is udpated.
 */

/*!
 \fn void Dir::filesChanged()
 Emitted when the internal file list is udpated.
 */

/*!
 \fn void Dir::sortChanged()
 Emitted when the \c sort is udpated.
 */

/*!
  \internal QDir::path()
 */
