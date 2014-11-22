#include "file.h"

File::File() : QFile(), QFileInfo() {

}

File::File(const QString &name, QObject *parent) : QFile(name, parent),
    QFileInfo(name)
{
}

bool File::exists() const { return QFileInfo::exists(); }

QString File::fileName() { return QFileInfo::fileName(); }

bool File::isReadable() const { return QFileInfo::isReadable(); }

bool File::isWritable() const { return QFileInfo::isWritable(); }

void File::setFileName(const QString& name) {
    QFile::setFileName(name);
    QFileInfo::setFile(name);
    emit fileNameChanged();
}
