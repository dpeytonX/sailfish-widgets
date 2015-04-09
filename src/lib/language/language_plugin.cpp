#include "language_plugin.h"
#include "localeitem.h"
#include "installedlocales.h"
#include "defaultlocale.h"

#include <qqml.h>

void LanguagePlugin::registerTypes(const char *uri)
{
    //@uri SailfishWidgets.Language
    qmlRegisterType<LocaleItem>(uri, 1, 3, "LocaleItem");
    qmlRegisterType<InstalledLocales>(uri, 1, 3, "InstalledLocales");
    qmlRegisterType<DefaultLocale>(uri, 1, 3, "DefaultLocale");
}


