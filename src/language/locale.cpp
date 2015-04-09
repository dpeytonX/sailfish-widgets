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
#include "locale.h"

/*!
   \class Locale
   \since 5.2
   \brief The Locale class

   \inmodule Language

   Represents a Locale (country and language).

   This class provides a way for QML to interpret locale strings (e.g. zh_CN) in a way that is easy to represent in a multi-lingual application.

   The country and language associated with the locale will be converted into the native language using Qt's existing functionality.

  Back to \l {Sailfish Widgets}
 */

/*!
 \fn Locale::Locale(QObject *parent)
 Constructs a new \l {Locale} using a \c QObject \a parent.
 */
Locale::Locale(QObject *parent) :
    QObject(parent), locale("")
{
}
/*!
 \fn Locale::Locale(const QString& locale, QObject *parent)
 Constructs a new \l {Locale} using a \a locale string and a \c QObject \a parent.
 */
Locale::Locale(const QString& locale, QObject *parent) : QObject(parent), m_locale(locale) {}

/*!
 \fn QString Locale::locale()
 Returns the locale.
 */
QString Locale::locale() const {
    return m_locale;
}

/*!
 \fn void Locale::setLocale(const QString& locale)
 Sets the internal locale to \a locale.
 */
void Locale::setLocale(const QString& locale) {
    m_locale = locale;
    emit localeChanged();
}

/*!
 \fn QString Locale::pretty() const
 Returns the locale represented in a user-friendly format with country and language translated into the native language.
 */
QString Locale::pretty() const {
    QString lang(language());
    QString ctry(country());
    if(ctry.isEmpty()) {
        return lang;
    }
    return lang + " (" + ctry + ")";
}

/*!
 \fn QString Locale::language() const
 Returns the language of the locale in its native language.
 */
QString Locale::language() const {
    return QLocale(m_locale).nativeLanguageName();
}

/*!
 \fn QString Locale::country(const QString& locale) const
 Returns the country of the locale in the native language.
 */
QString Locale::country() const {
    return QLocale(m_locale).nativeCountryName();
}

/*!
 \fn friend bool Locale::operator==(const Locale& lhs, const Locale& rhs)
 Friend function that compares \a lhs and \c rhs.

 Returns true if the \c {Locale} objects match.
 */

/*!
 \fn void Locale::localeChanged()
 Emitted when the locale string has changed.
 */

/*!
  \property Locale::language
  The locale's language translated in the locale's native language.
  */

/*!
  \property Locale::country
  The locale's country translated in the locale's native language.
  */

/*!
  \property Locale::pretty
  The locale represented in a user-friendly format with country and language translated into the native language.
  */

/*!
  \property Locale::locale
  The locale string
  */

/*!
 \fn bool operator==(const Locale& lhs, const Locale& rhs)
 Compares two \c {Locale} objects for equality-- \a lhs and \a rhs.

 Equality compares the internal locale string using \c QString equality.
 */
bool operator==(const Locale& lhs, const Locale& rhs) {
    return lhs.locale == rhs.locale;
}
