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

#include "applicationsettings.h"

/*!
   \class ApplicationSettings
   \since 5.0
   \brief The ApplicationSettings class

   \inmodule Settings

   This class will support one way (writing) of qml settings and loading at initialization time.

   Instantiate this QML object as you would any other and provide the applicationName and fileName. These applicationName will be "harbour-yourproject" and the fileName will be something like "settings" or "configuration". There is nothing technically stopping you from using multiple ApplicationSettings within the same application. However, until you provide both of these properties with actual values, this object will not persist any values.

   An example usage is as follows.
   \qml
    ApplicationSettings {
        id: settings
        applicationName: "harbour-applicationsettings"
        fileName: "settings"

        //By default, we want to show the user a tour of the app
        property bool performFirstRunWizard: true
    }
   \endqml

   We define an ApplicationSetting QML type for the \c harbour-applicationsettings application and give it the file name of "settings". (This will appear on the local user's home directory as .config/harbour-applicationsettings/settings). Next, we set the property \c performFirstRunWizard to \c true. This is only to provide a default value, and if the property exists, then it will be overwritten once the component has finished construction. Even if the property does not exist in the settings file, we would still have a valid property. If later on, we set \c performFirstRunWizard to \c false, then it will be persisted in the settings file.

   As of now, this QML type will not detect if the settings file was changed externally. Therefore, if your application has the need to set settings in multiple places, then you should take care to update the state of each ApplicationSettings as needed for data integrity.

   Back to \l {Sailfish Widgets}

 */

//Header file documentation

/*!
 \fn ApplicationSettings::ApplicationSettings(QQuickItem *parent = 0)
 Constructs a new \l {ApplicationSettings} with the given \c QQuickItem \a parent
 */

/*!
 \fn ApplicationSettings::~ApplicationSettings()
 */

/*!
 \fn void ApplicationSettings::setTarget(const QQmlProperty& qmlProperty)
 Sets the interal value of \a qmlProperty to whatever is stored in the settings file. If nothing is stored, then the \a qmlProperty's state will be unchanged and the value will instead be written into the settings file.
 */

/*!
 \fn void ApplicationSettings::updateProperty(const QString& propertyName, const QVariant& value)
 Updates the settings file with \a propertyName and \a value.
 */

/*!
 \fn void ApplicationSettings::qmlPropertyLookup(QmlPropertyWrapper *wrapper)
 When executed, this slot will get the \c QQmlProperty inside of \wrapper and call \c setTarget in order to update the settings file.

 \sa setTarget
 */

/*!
 \fn void ApplicationSettings::applicationNameChanged()
 Emitted when the \c applicationName has changed.
 */

/*!
 \fn void ApplicationSettings::fileNameChanged()
 Emitted when the \c fileName has changed.
 */

/*!
 \fn void ApplicationSettings::settingsInitialized()
 Emitted when the settings file has been created or accessed for the first time after loading.
 */
