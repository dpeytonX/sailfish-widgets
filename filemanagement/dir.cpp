#include "dir.h"

const QString Dir::m_configDir = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
const QString Dir::m_dataDir = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
const QString Dir::m_cacheDir = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
const QString Dir::m_homeDir = QDir::homePath();

Dir::Dir(QObject *parent) :
    QObject(parent),
    QDir(),
    m_fileList(QQmlListProperty<File>(this, 0,
                                      &Dir::dclAppendObject,
                                      &Dir::dclCountObject,
                                      &Dir::dclAtIndex,
                                      &Dir::dclClearObject))
{

}

QString Dir::dirName() const { return isRoot() ? root().path() : QDir::dirName(); }

QStringList Dir::entryList() {
    return QDir::entryList(Filters(m_filter) | QDir::Readable | QDir::NoDot, SortFlags(m_sort));
}

QQmlListProperty<File> Dir::files() {
    if(getList().isEmpty())
        foreach(QString s, entryList())
            getList().append(new File(absoluteFilePath(s), this));

    return m_fileList;
}

int Dir::filter() const { return m_filter; }

void Dir::refresh() {
    clearList();
    files();
    emit filesChanged();
}

void Dir::setFilter(int filter) {
    m_filter = filter;
    emit filterChanged();
}

void Dir::setPath(const QString &p) {
    QDir nPath(p);
    //Weird workaround for inifinite /../..
    QDir::setPath(nPath.path() == "/.." ? "/" : nPath.absolutePath());
    emit pathChanged();
}

void Dir::setSort(int sort) {
    m_sort = sort;
    emit sortChanged();
}

int Dir::sort() const { return m_sort; }
