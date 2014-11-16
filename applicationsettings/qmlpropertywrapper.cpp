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

#include "qmlpropertywrapper.h"

/*!
   \class QmlPropertyWrapper
   \since 5.0
   \brief The QmlPropertyWrapper class

   \inmodule Settings

   This class was created because connecting to a signal against \c QQmlProperty that is determined at run time is difficult. The simplest way was to create a wrapper (this class) which provides a signal with the \c QQmlProperty as a parameter so that the receiver slots can perform different actions depending on the QQmlProperty that emitted the original signal.

   Back to \l {Sailfish Widgets}

 */

/*!
  \fn QmlPropertyWrapper::QmlPropertyWrapper(QQmlProperty property, QObject *parent)
  Constructs a new \l {QmlPropertyWrapper} with the given \c QQmlProperty \a property and \c QObject \a parent
 */
QmlPropertyWrapper::QmlPropertyWrapper(QQmlProperty property, QObject *parent) :
    QObject(parent),
    m_property(property)
{
    property.connectNotifySignal(this, SLOT(notified()));
}

/*!
  \fn void QmlPropertyWrapper::notified()
  This slot is executed when the internal \c QQmlProperty \c connectNotifySignal is emitted.
 */
void QmlPropertyWrapper::notified() {
    emit notifySignal(this);
}

// Header file function documentation

/*!
  \fn QQmlProperty QmlPropertyWrapper::property() const
  Returns the internal \c QQmlProperty.
 */

/*!
  \fn void QmlPropertyWrapper::notifySignal(QmlPropertyWrapper *property)
  Emitted when the \c connectNotifySignal of the \a property is emitted.
 */
