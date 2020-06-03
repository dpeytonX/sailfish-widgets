#include "database_plugin.h"
#include "sqlitedatabase.h"
#include "query.h"

#include <qqml.h>

void DatabasePlugin::registerTypes(const char *uri)
{
    // @uri SailfishWidgets.Database
    qmlRegisterType<SQLiteDatabase>(uri, 3, 3, "SQLiteDatabase");
    qmlRegisterType<Query>(uri, 3, 3, "Query");
}


