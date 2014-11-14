#include "applicationsettings_plugin.h"
#include "applicationsettings.h"

#include <qqml.h>

void ApplicationsettingsPlugin::registerTypes(const char *uri)
{
    // @uri SailfishWidgets.Util
    qmlRegisterType<ApplicationSettings>(uri, 1, 0, "ApplicationSettings");
}


