#ifndef QMLPROPERTYWRAPPER_H
#define QMLPROPERTYWRAPPER_H

#include <QObject>
#include <QQmlProperty>

class QmlPropertyWrapper : public QObject
{
    Q_OBJECT
public:
    explicit QmlPropertyWrapper(QQmlProperty property, QObject *parent = 0);

    QQmlProperty property() const {return m_property;}

signals:
    void notifySignal(QmlPropertyWrapper *property);

public slots:
    void notified();

private:
    QQmlProperty m_property;

};

#endif // QMLPROPERTYWRAPPER_H
