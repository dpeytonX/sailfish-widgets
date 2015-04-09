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

#include "installedlocales.h"

#include <QDir>
#include <QList>
#include <QQmlListProperty>
#include <QStringList>

#include "locale.h"

#include <sailfishapp.h>

/*!
   \class InstalledLocales
   \since 5.2
   \brief The InstalledLocales class

   \inmodule Language

  Gets the locales available to the application for translation.

  This application will retrieve the harbour-*.qm files and strip the locale suffix then convert them
  into QML objects that client applications can then access and show to the user.

  This class can also inject a default application locale (user specified) so that end-user apps can
  use a single model to represent all possible language selections to the user.

  Back to \l {Sailfish Widgets}
 */

/*!
 \fn InstalledLocales::InstalledLocales(QObject *parent)
 Constructs a new \l {InstalledLocales}
 */
InstalledLocales::InstalledLocales(QObject *parent) : QObject(parent),
    m_availableLocales(), m_includeAppDefault(true) {

    QDir dir(SailfishApp::pathTo(QString("translations")).toLocalFile());
    QStringList qmlFiles = dir.entryList();
    for(const QString& qmlFile : qmlFiles) {
        int posQm = qmlFile.lastIndexOf(".qm");
        if(app.size() >= qmlFile.size() || app.size() >= posQm || posQm == -1) continue;
        m_availableLocales(qmlFile.mid(app.size() + 1, posQm - app.size() - 1));
    }
}

/*!
 \internal
 */
Locale* InstalledLocales::localeAt(QQmlListProperty<Locale> *property, int index) {
    return &m_availableLocales[index];
}

/*!
 \internal
 */
int InstalledLocales::localeCount(QQmlListProperty<Locale> *property) {
    return m_availableLocales.size();
}

/*!
 \fn bool InstalledLocales::includeAppDefault() const
 Returns whether to include a default application locale with the installed locales.

 This will insert a new \c {DefaultLocale} object at index 0.
 */
bool InstalledLocales::includeAppDefault() const {
    return m_includeAppDefault;
}

/*!
 \fn void InstalledLocales::setIncludeAppDefault(bool includeAppDefault)

 Sets the option \a includeAppDefault to include a \c {DefaultLocale} in the locale model returned by this object.
 */
void InstalledLocales::setIncludeAppDefault(bool includeAppDefault) {
    m_includeAppDefault = includeAppDefault;

    for(Locale l : m_availableLocales) {
        if(l.locale() == DefaultLocale::APPLICATION_LOCALE) {
            m_availableLocales.removeOne(l);
            break;
        }
    }
    if(m_availableLocales)
        m_availableLocales.insert(0, DefaultLocale(this));
    emit localesChanged();
}

/*!
 \fn QQmlListProperty<Locale> InstalledLocales::locales() const
 Returns the installed locales for your application.

 These are determined by the translation \c .qm files that are installed in the translations
 directory for your application.

 The non-localed translation (harbour-your_app.qm) is only included unless you set the includeAppDefault property to false.
 */
QQmlListProperty<Locale> InstalledLocales::locales() const {
    return QQmlListProperty(this, nullptr, localeCount, localeAt);
}

/*!
 \fn void InstalledLocales::localesChanged()
 Emitted when the \c the internal locales list has changed.

 This is only updated if the \c includeAppDefault variable is updated.
 */
void localesChanged();

/*!
  \property InstalledLocales::includeAppDefault
  Whether the default locale is included in the locales list.
  */

/*!
  \property InstalledLocales::locales
  The locales provided by your app.
  */
