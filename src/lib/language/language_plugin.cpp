#include "language_plugin.h"
#include "installedlocales.h"
#include "locale.h"
#include "defaultlocale.h"

#include <qqml.h>

void LanguagePlugin::registerTypes(const char *uri)
{
    // @uri SailfishWidgets.Language
    qmlRegisterType<InstalledLocales>(uri, 1, 3, "InstalledLocales");
    qmlRegisterType<Locale>(uri, 1, 3, "Locale");
    qmlRegisterType<DefaultLocale>(uri, 1, 3, "DefaultLocale");
}


