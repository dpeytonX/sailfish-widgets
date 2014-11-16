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

#ifndef APPLICATIONSETTINGS_H
#define APPLICATIONSETTINGS_H

#include <QEvent>
#include <QByteArray>
#include <QList>
#include <QQmlParserStatus>
#include <QQuickItem>
#include <QString>
#include <QSettings>
#include <QQmlProperty>
#include <QMap>
#include <QStringList>

#include "qmlpropertywrapper.h"

class ApplicationSettings : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(ApplicationSettings)
    Q_INTERFACES(QQmlParserStatus)

    Q_PROPERTY(QString applicationName READ applicationName WRITE setApplicationName NOTIFY applicationNameChanged)
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)

public:
    ApplicationSettings(QQuickItem *parent = 0) : QQuickItem(parent),
        m_existingProperties(new QStringList()),
        m_initialized(false),
        m_pending(new QMap<QString, QVariant>()),
        m_settings(0),
        m_userProperties(new QList<QmlPropertyWrapper*>()) {

        const QMetaObject* myMetaObj = metaObject();
        for(int i = 0; i < myMetaObj->propertyCount();i++) {
            QMetaProperty property = myMetaObj->property(i);
            //Build up a list of pre-existing properties (hackish)
            m_existingProperties->append(property.name());
        }
    }

    ~ApplicationSettings() {
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
    QString applicationName() const {
        return m_applicationName;
    }

    /*!
      \property ApplicationSettings::fileName
      \brief The name of the settings file.

      In general, this should be set to "settings" or "config". You may choose to name the settings file based on the configuration data inside, however.

      \sa ApplicationSettings::fileName()
     */
    QString fileName() const {
        return m_fileName;
    }

    void setApplicationName(QString appName) {
        m_applicationName = appName;
        emit applicationNameChanged();
        if (isSettingsValid()) emit settingsInitialized();
    }

    void setFileName(QString fileName) {
        m_fileName = fileName;
        emit fileNameChanged();
        if (isSettingsValid()) emit settingsInitialized();
    }

public slots:
    void setTarget(const QQmlProperty& qmlProperty) {
        if(!qmlProperty.isValid() || qmlProperty.propertyType() == QVariant::Invalid) return;

        // Skip applicationName and fileName
        if(qmlProperty.name() == "applicationName" || qmlProperty.name() == "fileName") return;

        // Notify settings updater that property changed
        updateProperty(qmlProperty.name(), qmlProperty.read());
    }

    void updateProperty(const QString& propertyName, const QVariant& value) {
        if(m_settings == 0) {
            m_pending->insert(propertyName, value);
            return;
        }
        m_settings->setValue(propertyName, value);
    }

private slots:
    void qmlPropertyLookup(QmlPropertyWrapper *wrapper) {
        setTarget(wrapper->property());
    }

signals:
    void applicationNameChanged();
    void fileNameChanged();
    void settingsInitialized();

private:
    void firstLoad() {
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

    bool isSettingsValid() {
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

    QString m_applicationName;
    QStringList* m_existingProperties;
    QString m_fileName;
    bool m_initialized;
    QMap<QString, QVariant>* m_pending;
    QSettings* m_settings;
    QList<QmlPropertyWrapper*>* m_userProperties;
};

#endif // APPLICATIONSETTINGS_H

