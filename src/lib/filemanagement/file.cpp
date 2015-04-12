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

#include <QTextStream>

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
   \enum File::OpenModeFlag

   Provides the flags available for opening files.

   \value NotOpen = 0x0000,
   \value ReadOnly = 0x0001,
   \value WriteOnly = 0x0002,
   \value ReadWrite = ReadOnly | WriteOnly,
   \value Append = 0x0004,
   \value Truncate = 0x0008,
   \value Text = 0x0010,
   \value Unbuffered = 0x0020
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
 \fn File::fileName()
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
 \fn void File::setFileName(const QString& name)
 Sets the file name to \a name.
 */
void File::setFileName(const QString& name) {
    QFile::setFileName(name);
    QFileInfo::setFile(name);
    emit fileNameChanged();
}

/*!
 \fn bool File::open(int mode)

 It will take the \c OpenModeFlags indicated by \a mode and open the file.

 Returns true if successful.
 */
bool File::open(int mode) {
    return QFile::open(OpenMode(mode));
}

/*!
 \fn void File::close()

 Closes the file.
 */
void File::close() {
    QFile::close();
}

/*!
 \fn QString File::readAll()

 Reads the file in a \c QTextStream and returns the contents.
 */
QString File::readAll() {
    return QTextStream(this).readAll();
}

/*!
 \fn void File::write(const QString& text)

 Writes \a text to the file and returns the contents.
 */
void File::write(const QString& text) {
    QTextStream(this) << text;
}

/*!
 \fn bool File::remove()

 Removes this file from the file system.

 Returns true if successful.
 */
bool File::remove() {
    return QFile::remove();
}

/*!
 \fn bool File::rename(const QString &newName)

 Renames this file to \a newName.

 Returns true if successful.
 */
bool File::rename(const QString &newName) {
    return QFile::rename(newName);
}

/*!
 \fn bool File::copy(const QString &newName)

 Copies the this file to the file located at \a newName.

 Returns true if successful.
 */
bool File::copy(const QString &newName) {
    return QFile::copy(newName);
}

/*!
 \fn void File::fileNameChanged()
 Emitted when the \c the file name is changed.
 */

/*!
  \property File::dir
  True if this object points to a directory.
  */
/*!
  \property File::executable
  True if this object is executable.
  */
/*!
  \property File::exists
  True if this object exists.
  */
/*!
  \property File::file
  True if this object points to a file.
  */
/*!
  \property File::hidden
  True if this object is hidden.
  */
/*!
  \property File::readable
  True if this object is readable.
  */
/*!
  \property File::root
  True if this object points to the root directory.
  */
/*!
  \property File::symLink
  True if this object points to a symbolic link.
  */
/*!
  \property File::writable
  True if this object is writable.
  */
/*!
  \property File::absoluteFilePath
  Holds the absolute path with file name.
  */
/*!
  \property File::fileName
  Holds the file name without the path prepended.
  */
