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

/*!
 \fn ApplicationSettings::ApplicationSettings()
 Constructs a new \l {ApplicationSettings}
 */
ApplicationSettings::ApplicationSettings() : QQuickItem(0),
    m_initialized(false),
    m_pending(new QMap<QString, QVariant>()),
    m_userProperties(new QList<QmlPropertyWrapper*>()),
    m_settings(0),
    m_existingProperties(new QStringList())
{
}

/*!
 \fn ApplicationSettings::ApplicationSettings(QQuickItem *parent)
 Constructs a new \l {ApplicationSettings} with the given \c QQuickItem \a parent
 */
ApplicationSettings::ApplicationSettings(QQuickItem *parent) : QQuickItem(parent),
    m_initialized(false),
    m_pending(new QMap<QString, QVariant>()),
    m_userProperties(new QList<QmlPropertyWrapper*>()),
    m_settings(0),
    m_existingProperties(new QStringList())
{
    const QMetaObject* myMetaObj = metaObject();
    for(int i = 0; i < myMetaObj->propertyCount();i++) {
        QMetaProperty property = myMetaObj->property(i);
        //Build up a list of pre-existing properties (hackish)
        m_existingProperties->append(property.name());
    }
}
/*!
 \fn ApplicationSettings::~ApplicationSettings()
 */
ApplicationSettings::~ApplicationSettings() {
    if(m_pending != 0)
        delete m_pending;

    if(m_existingProperties != 0)
        delete m_existingProperties;

    if(m_userProperties != 0) {
        for(int i = 0; i < m_userProperties->size(); i++) {
            delete m_userProperties->at(i);
        }
        m_userProperties->clear();
        delete m_userProperties;
    }
}

/*!
   \property ApplicationSettings::applicationName
   \brief The application's name.

   This property is passed to QSettings in order to create the application configuration directory where the settings file will be stored. It must be "harbour-yourapp" in order to pass sandboxing requirements.

   \sa ApplicationSettings::applicationName()
 */
QString ApplicationSettings::applicationName() const {
    return m_applicationName;
}

void ApplicationSettings::setApplicationName(QString appName) {
    m_applicationName = appName;
    emit applicationNameChanged();
    if (isSettingsValid()) emit settingsInitialized();
}

/*!
   \property ApplicationSettings::fileName
   \brief The name of the settings file.

   In general, this should be set to "settings" or "config". You may choose to name the settings file based on the configuration data inside, however.

   \sa ApplicationSettings::fileName()
 */
QString ApplicationSettings::fileName() const {
    return m_fileName;
}

void ApplicationSettings::setFileName(QString fileName) {
    m_fileName = fileName;
    emit fileNameChanged();
    if (isSettingsValid()) emit settingsInitialized();
}


/*!
 \fn void ApplicationSettings::setTarget(const QQmlProperty& qmlProperty)
 Sets the interal value of \a qmlProperty to whatever is stored in the settings file. If nothing is stored, then the \a qmlProperty's state will be unchanged and the value will instead be written into the settings file.
 */
void ApplicationSettings::setTarget(const QQmlProperty& qmlProperty) {
    if(!qmlProperty.isValid() || qmlProperty.propertyType() == QVariant::Invalid) return;

    // Skip applicationName and fileName
    if(qmlProperty.name() == "applicationName" || qmlProperty.name() == "fileName") return;

    // Notify settings updater that property changed
    updateProperty(qmlProperty.name(), qmlProperty.read());
}

/*!
 \fn void ApplicationSettings::updateProperty(const QString& propertyName, const QVariant& value)
 Updates the settings file with \a propertyName and \a value.
 */
void ApplicationSettings::updateProperty(const QString& propertyName, const QVariant& value) {
    if(m_settings == 0) {
        m_pending->insert(propertyName, value);
        return;
    }
    m_settings->setValue(propertyName, value);
}

/*!
 \fn void ApplicationSettings::qmlPropertyLookup(QmlPropertyWrapper *wrapper)
 When executed, this slot will get the \c QQmlProperty inside of \wrapper and call \c setTarget in order to update the settings file.

 \sa setTarget
 */
void ApplicationSettings::qmlPropertyLookup(QmlPropertyWrapper *wrapper) {
    setTarget(wrapper->property());
}

void ApplicationSettings::firstLoad() {
    if(m_settings == 0 || m_initialized) return;
    m_initialized = true;

    const QMetaObject* myMetaObj = metaObject();
    for(int i = 0; i < myMetaObj->propertyCount();i++) {
        QMetaProperty property = myMetaObj->property(i);

        QQmlProperty qmlProperty(this, property.name());
        if(!qmlProperty.isValid() || qmlProperty.propertyType() == QVariant::Invalid) continue;

        // Skip applicationName and fileName
        if(qmlProperty.name() == "applicationName" || qmlProperty.name() == "fileName") continue;

        //Don't persist class properties (only user defined ones)
        if(m_existingProperties->contains(qmlProperty.name())) continue;

        QVariant value = m_settings->value(qmlProperty.name(), QVariant(QVariant::Invalid));
        if(value.isValid())
            // We already have a value, so prefer settings over default
            qmlProperty.write(value);
        else
            // Populate settings with value
            updateProperty(qmlProperty.name(), qmlProperty.read());

        // Add notification handler
        QmlPropertyWrapper* wrapper = new QmlPropertyWrapper(qmlProperty);
        m_userProperties->append(wrapper);
        connect(wrapper, SIGNAL(notifySignal(QmlPropertyWrapper*)), this,
                SLOT(qmlPropertyLookup(QmlPropertyWrapper*)));
    }
}

bool ApplicationSettings::isSettingsValid() {
    if(!m_applicationName.isEmpty() && !m_fileName.isEmpty()) {
        m_settings = new QSettings(m_applicationName, m_fileName, this);
        QMap<QString, QVariant>::const_iterator i = m_pending->constBegin();
        while (i != m_pending->constEnd()) {
            updateProperty(i.key(), i.value());
            ++i;
        }
        delete m_pending; m_pending = 0;
        firstLoad();
        return true;
    }
    return false;
}

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
