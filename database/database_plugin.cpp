#include "database_plugin.h"
#include "sqlitedatabase.h"
#include "query.h"

#include <qqml.h>

void DatabasePlugin::registerTypes(const char *uri)
{
    // @uri SailfishWidgets.Database
    qmlRegisterType<SQLiteDatabase>(uri, 1, 3, "SQLiteDatabase");
    qmlRegisterType<Query>(uri, 1, 3, "Query");
}


