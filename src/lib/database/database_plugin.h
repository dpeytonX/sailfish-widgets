#ifndef DATABASE_PLUGIN_H
#define DATABASE_PLUGIN_H

#include <QQmlExtensionPlugin>

class DatabasePlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri);
};

#endif // DATABASE_PLUGIN_H

