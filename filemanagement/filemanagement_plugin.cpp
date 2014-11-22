#include "filemanagement_plugin.h"
#include "dir.h"
#include "file.h"

#include <qqml.h>

void FilemanagementPlugin::registerTypes(const char *uri)
{
    // @uri SailfishWidgets.FileManagement
    qmlRegisterType<Dir>(uri, 1, 2, "Dir");
    qmlRegisterType<File>(uri, 1, 2, "File");
}


