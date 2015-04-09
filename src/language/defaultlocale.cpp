/***************************************************************************
** This file is part of SailfishWidgets
**
** Copyright (c) 2015 Dametrious Peyton
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
#include "defaultlocale.h"

/*!
   \class DefaultLocale
   \since 5.2
   \brief The DefaultLocale class

   \inmodule Language

  Applications usually have a default translation file which is not suffixed with a country/region specifier.

  This special file is given the locale of APPLICATION_LOCALE and instead of corresponding to a specific language, it just represents
  the default translation bundle if no others have been installed.

  Back to \l {Sailfish Widgets}
 */

DefaultLocale::APPLICATION_LOCALE("app");

/*!
 \fn DefaultLocale::DefaultLocale(QObject* parent)
 Constructs a new \l {DefaultLocale} using a \c QObject \a parent.
 */
DefaultLocale::DefaultLocale(QObject* parent) : Locale(parent, APPLICATION_LOCALE) {
}

/*!
 \fn QString DefaultLocale::pretty() const
 Returns whatever the applicationDefaultText has been set to.
 */
QString DefaultLocale::pretty() const {
    return m_applicationDefaultText;
}

/*!
 \fn void DefaultLocale::setApplicationDefaultText(const QString& applicationDefaultText)
 Sets the translated text \a applicationDefaultText that should appear instead of "Application Default".
 */
void DefaultLocale::setApplicationDefaultText(const QString& applicationDefaultText) {
    m_applicationDefaultText = applicationDefaultText;
    emit applicationDefaultTextChanged();
}

/*!
 \fn QString DefaultLocale::applicationLocale() const
 Returns the static constant that represents the locale string for the default application's locale.
 */
QString DefaultLocale::applicationLocale() const {
    return APPLICATION_LOCALE;
}

/*!
 \fn void DefaultLocale::applicationDefaultTextChanged()
 Emitted when the application default text has changed.
 */

/*!
  \property DefaultLocale::applicationDefaultText
  This is the \a qsTr string that you can use to represent the default application local. For example, "Application Default" in English or "アップリの規定" in Japanese.
  */

/*!
  \property DefaultLocale::applicationLocale
  The static constant that represents the locale string for the default application's locale.
  */
