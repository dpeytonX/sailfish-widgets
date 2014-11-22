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

#include "file.h"

/*!
   \class File
   \since 5.0
   \brief The File class

   \inmodule FileManagement

   This class will expose \c QFileInfo and \c QFile functionality to QML.

   An example QML usage:
   \qml
   File {
        id: fileList
        fileName: "myfile.txt"
    }
   \endqml


   Back to \l {Sailfish Widgets}

 */

/*!
 \fn File::File()
 Constructs a new \l {File} with no file reference
 */
File::File() : QFile(), QFileInfo() {

}

/*!
 \fn File::File(const QString &name, QObject *parent)
 Constructs a new \l {File} linked to file name \a name and given a \c QObject \a parent.
 */
File::File(const QString &name, QObject *parent) : QFile(name, parent),
    QFileInfo(name)
{
}

/*!
 \fn File::exists() const
 Returns \c true if the file exists on the file system.
 */
bool File::exists() const { return QFileInfo::exists(); }

/*!
 \fn File::fileName() const
 Returns the current file path of the file.
 */
QString File::fileName() { return QFileInfo::fileName(); }

/*!
 \fn File::isReadable() const
 Returns \c true if the file is readable.
 */
bool File::isReadable() const { return QFileInfo::isReadable(); }

/*!
 \fn File::isWritable() const
 Returns \c true if the file is writable.
 */
bool File::isWritable() const { return QFileInfo::isWritable(); }

/*!
 \fn File::setFileName(QString &name)
 Sets the file name to \a name.
 */
void File::setFileName(const QString& name) {
    QFile::setFileName(name);
    QFileInfo::setFile(name);
    emit fileNameChanged();
}


/*!
 \fn void File::fileNameChanged()
 Emitted when the \c the file name is changed.
 */
