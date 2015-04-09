#include "language_plugin.h"
#include "locale.h"
//#include "installedlocales.h"
//#include "defaultlocale.h"

#include <qqml.h>

void LanguagePlugin::registerTypes(const char *uri)
{
    //@uri SailfishWidgets.Language
    qmlRegisterType<Locale>(uri, 1, 3, "Locale");
    //qmlRegisterType<InstalledLocales>(uri, 1, 3, "InstalledLocales");

    //qmlRegisterType<DefaultLocale>(uri, 1, 3, "DefaultLocale");
}


