#ifndef APPLICATIONSETTINGS_H
#define APPLICATIONSETTINGS_H

#include <QDebug>
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

/**
 * @brief The ApplicationSettings class
 *
 * This class will support one way (writing) of qml settings and loading at initialization time.
 *
 */
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

        qDebug() << "constructor";
        const QMetaObject* myMetaObj = metaObject();
        for(int i = 0; i < myMetaObj->propertyCount();i++) {
            QMetaProperty property = myMetaObj->property(i);
            qDebug() << property.name() << property.isUser(this);
            //Build up a list of pre-existing properties (hackish)
            m_existingProperties->append(property.name());
        }
    }

    ~ApplicationSettings() {
        if(m_pending != 0) {
            qDebug() << "deleting pending";
            delete m_pending;
        }
        if(m_existingProperties != 0) {
            qDebug() << "deleting existing props";
            delete m_existingProperties;
        }
        if(m_userProperties != 0) {
            for(int i = 0; i < m_userProperties->size(); i++) {
                qDebug() << "deleting user property at " << i;
                delete m_userProperties->at(i);
            }
            m_userProperties->clear();
            qDebug() << "deleting user property list ";
            delete m_userProperties;
        }
    }

    QString applicationName() const {
        return m_applicationName;
    }

    QString fileName() const {
        return m_fileName;
    }

    void setApplicationName(QString appName) {
        qDebug() << "setApplicationName" << appName;
        m_applicationName = appName;
        emit applicationNameChanged();
        if (isSettingsValid()) emit settingsInitialized();
    }

    void setFileName(QString fileName) {
        qDebug() << "setFileName" << fileName;
        m_fileName = fileName;
        emit fileNameChanged();
        if (isSettingsValid()) emit settingsInitialized();
    }

signals:
    void applicationNameChanged();
    void fileNameChanged();
    void settingsInitialized();

public slots:
    void setTarget(const QQmlProperty& qmlProperty) {
        qDebug() << "setTarget " << qmlProperty.name() << qmlProperty.read();
        if(!qmlProperty.isValid() || qmlProperty.propertyType() == QVariant::Invalid) return;

        // Skip applicationName and fileName
        if(qmlProperty.name() == "applicationName" || qmlProperty.name() == "fileName") return;

        // Notify settings updater that property changed
        updateProperty(qmlProperty.name(), qmlProperty.read());
    }

    void updateProperty(const QString& propertyName, const QVariant& value) {
        qDebug() << "updateProperty " << propertyName << value;
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

private:
    void firstLoad() {
        if(m_settings == 0 || m_initialized) return;
        m_initialized = true;

        qDebug() << "firstLoad()";
        const QMetaObject* myMetaObj = metaObject();
        for(int i = 0; i < myMetaObj->propertyCount();i++) {
            QMetaProperty property = myMetaObj->property(i);
            qDebug() << property.name() << property.isUser(this);

            QQmlProperty qmlProperty(this, property.name());
            if(!qmlProperty.isValid() || qmlProperty.propertyType() == QVariant::Invalid) continue;

            // Skip applicationName and fileName
            if(qmlProperty.name() == "applicationName" || qmlProperty.name() == "fileName") continue;

            //Don't persist class properties (only user defined ones)
            if(m_existingProperties->contains(qmlProperty.name())) continue;

            QVariant value = m_settings->value(qmlProperty.name(), QVariant(QVariant::Invalid));
            if(value.isValid()) {
                // We already have a value, so prefer settings over default
                qDebug() << "set qml value " << qmlProperty.name() << value;
                qmlProperty.write(value);
            } else {
                // Populate settings with value
                updateProperty(qmlProperty.name(), qmlProperty.read());
            }

            // Add notification handler
            QmlPropertyWrapper* wrapper = new QmlPropertyWrapper(qmlProperty);
            m_userProperties->append(wrapper);
            connect(wrapper, SIGNAL(notifySignal(QmlPropertyWrapper*)), this,
                    SLOT(qmlPropertyLookup(QmlPropertyWrapper*)));
        }
    }

    bool isSettingsValid() {
        qDebug() << "isSettingsValid " << m_applicationName << " filename: " << m_fileName;
        if(!m_applicationName.isEmpty() && !m_fileName.isEmpty()) {
            m_settings = new QSettings(m_applicationName, m_fileName, this);
            QMap<QString, QVariant>::const_iterator i = m_pending->constBegin();
            while (i != m_pending->constEnd()) {
                updateProperty(i.key(), i.value());
                ++i;
            }
            qDebug() << "deleting pending list with size " << m_pending->size();
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

