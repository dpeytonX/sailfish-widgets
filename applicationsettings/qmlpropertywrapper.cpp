#include "qmlpropertywrapper.h"

QmlPropertyWrapper::QmlPropertyWrapper(QQmlProperty property, QObject *parent) :
    QObject(parent),
    m_property(property)
{
    property.connectNotifySignal(this, SLOT(notified()));
}

void QmlPropertyWrapper::notified() {
    emit notifySignal(this);
}
