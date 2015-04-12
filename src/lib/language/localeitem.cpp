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
#include "localeitem.h"


#include <QLocale>
#include <QString>

/*!
   \class LocaleItem
   \since 5.2
   \brief The LocaleItem class

   \inmodule Language

   Represents a Locale (country and language).

   This class provides a way for QML to interpret locale strings (e.g. zh_CN) in a way that is easy to represent in a multi-lingual application.

   The country and language associated with the locale will be converted into the native language using Qt's existing functionality.

  Back to \l {Sailfish Widgets}
 */

/*!
 \fn LocaleItem::LocaleItem(QQuickItem *parent)
 Constructs a new \l {LocaleItem} using a \c QObject \a parent.
 */
LocaleItem::LocaleItem(QQuickItem *parent) :
    QQuickItem(parent), m_locale("")
{
}
/*!
 \fn LocaleItem::LocaleItem(const QString& locale, QQuickItem *parent)
 Constructs a new \l {LocaleItem} using a \a locale string and a \c QObject \a parent.
 */
LocaleItem::LocaleItem(const QString& locale, QQuickItem *parent) : QQuickItem(parent), m_locale(locale) {}

/*!
 \fn QString LocaleItem::locale() const
 Returns the locale.
 */
QString LocaleItem::locale() const {
    return m_locale;
}

/*!
 \fn void LocaleItem::setLocale(const QString& locale)
 Sets the internal locale to \a locale.
 */
void LocaleItem::setLocale(const QString& locale) {
    m_locale = locale;
    emit localeChanged();
}

/*!
 \fn QString LocaleItem::pretty() const
 Returns the locale represented in a user-friendly format with country and language translated into the native language.
 */
QString LocaleItem::pretty() const {
    QString lang(language());
    QString ctry(country());
    if(ctry.isEmpty()) {
        return lang;
    }
    return lang + " (" + ctry + ")";
}

/*!
 \fn QString LocaleItem::language() const
 Returns the language of the locale in its native language.
 */
QString LocaleItem::language() const {
    return QLocale(m_locale).nativeLanguageName();
}

/*!
 \fn QString LocaleItem::country() const
 Returns the country of the locale in the native language.
 */
QString LocaleItem::country() const {
    return QLocale(m_locale).nativeCountryName();
}

/*!

 \relates LocaleItem

 fn bool operator==(const Locale& lhs, const Locale& rhs)
 Compares two \c {Locale} objects for equality-- \a lhs and \a rhs.

 Equality compares the internal locale string using \c QString equality.
 */
bool operator==(const LocaleItem& lhs, const LocaleItem& rhs) {
    return lhs.m_locale == rhs.m_locale;
}

/*!
 \fn void LocaleItem::localeChanged()
 Emitted when the locale string has changed.
 */

/*!
  \property LocaleItem::language
  The locale's language translated in the locale's native language.
  */

/*!
  \property LocaleItem::country
  The locale's country translated in the locale's native language.
  */

/*!
  \property LocaleItem::pretty
  The locale represented in a user-friendly format with country and language translated into the native language.
  */

/*!
  \property LocaleItem::locale
  The locale string
  */
