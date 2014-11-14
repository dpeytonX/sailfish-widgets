#ifndef APPLICATIONSETTINGS_PLUGIN_H
#define APPLICATIONSETTINGS_PLUGIN_H

#include <QQmlExtensionPlugin>

class ApplicationsettingsPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);
};

#endif // APPLICATIONSETTINGS_PLUGIN_H

