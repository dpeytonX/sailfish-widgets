#include "applicationsettings_plugin.h"
#include "applicationsettings.h"

#include <qqml.h>

void ApplicationsettingsPlugin::registerTypes(const char *uri)
{
    // @uri SailfishWidgets.Settings
    qmlRegisterType<ApplicationSettings>(uri, 1, 1, "ApplicationSettings");
}


