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
#include <QStringList>

#include <sailfishapp.h>

#include "defaultlocale.h"

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
 \fn InstalledLocales::InstalledLocales(QQuickItem *parent)
 Constructs a new \l {InstalledLocales} using a \c QQuickItem \a parent
 */
InstalledLocales::InstalledLocales(QQuickItem *parent) : QQuickItem(parent),
    m_availableLocales(QList<LocaleItem*>()), m_appName(""), m_includeAppDefault(true)  {
}

/*!
 \internal
 */
LocaleItem* InstalledLocales::localeAt(QQmlListProperty<LocaleItem> *property, int index) {
    return (*((QList<LocaleItem*> *)property->data))[index];
}

/*!
 \internal
 */
int InstalledLocales::localeCount(QQmlListProperty<LocaleItem> *property) {
    return (((QList<LocaleItem*> *)property->data))->size();
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

    for(LocaleItem* l : m_availableLocales) {
        if(l->locale() == DefaultLocale::APPLICATION_LOCALE) {
            m_availableLocales.removeOne(l);
            l->deleteLater();
            break;
        }
    }
    if(m_availableLocales.isEmpty())
        m_availableLocales.insert(0, new DefaultLocale(this));
    emit localesChanged();
}

/*!
 \fn QQmlListProperty<Locale> InstalledLocales::locales()
 Returns the installed locales for your application.

 These are determined by the translation \c .qm files that are installed in the translations
 directory for your application.

 The non-localed translation (harbour-your_app.qm) is only included unless you set the includeAppDefault property to false.
 */
QQmlListProperty<LocaleItem> InstalledLocales::locales() {
    return QQmlListProperty<LocaleItem>(this, &m_availableLocales, &(InstalledLocales::localeCount), &(InstalledLocales::localeAt));
}

/*!
 \fn QString InstalledLocales::appName() const
 Returns the application name.
 */
QString InstalledLocales::appName() const {
    return m_appName;
}

/*!
 \fn void InstalledLocales::setAppName(const QString& appName)
 Sets the application's name to \a appName .

 You must set the application name in order for \l {InstalledLocales} to be able to find the appropriate translation units.
 */
void InstalledLocales::setAppName(const QString& appName) {
    m_appName = appName;
    emit appNameChanged();

    for(LocaleItem* l : m_availableLocales) {
        l->deleteLater();
    }
    m_availableLocales.clear();

    QDir dir(SailfishApp::pathTo(QString("translations")).toLocalFile());
    QStringList qmlFiles = dir.entryList();
    for(const QString& qmlFile : qmlFiles) {
        int posQm = qmlFile.lastIndexOf(".qm");
        if(m_appName.size() >= qmlFile.size() || m_appName.size() >= posQm || posQm == -1) continue;
        m_availableLocales.append(new LocaleItem(qmlFile.mid(m_appName.size() + 1, posQm - m_appName.size() - 1), this));
    }
    setIncludeAppDefault(m_includeAppDefault);
}

/*!
 \fn void InstalledLocales::localesChanged()
 Emitted when the \c the internal locales list has changed.

 This is only updated if the \c includeAppDefault variable is updated.
 */

/*!
 \fn void InstalledLocales::appNameChanged()
 Emitted when the \c the application's name is changed.

 This will also update the available locales list.
 */

/*!
  \property InstalledLocales::includeAppDefault
  Whether the default locale is included in the locales list.
  */

/*!
  \property InstalledLocales::locales
  The locales provided by your app.
  */

/*!
  \property InstalledLocales::appName
  The application's name.
  */
