TEMPLATE = lib
TARGET = database
QT += qml quick
CONFIG += qt plugin

QT += sql

QMAKE_CXXFLAGS += "-std=c++0x"

TARGET = $$qtLibraryTarget($$TARGET)
uri = SailfishWidgets.Database

# Input
SOURCES += \
    database_plugin.cpp \
    sqlitedatabase.cpp \
    query.cpp

HEADERS += \
    database_plugin.h \
    sqlitedatabase.h \
    query.h

OTHER_FILES =

contains( CMD_LINE, "true") {
  !equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/../../qml/SailfishWidgets/Database/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
  }

  qmldir.files = qmldir
  unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
  }
}

!contains( CONFIG, "DEBUG") {
    strip_lib.target = strlib
    strip_lib.depends = all
    strip_lib.commands = $(STRIP) --strip-all $(TARGET)
    QMAKE_EXTRA_TARGETS += strip_lib
}

isEmpty( CMD_LINE) {
  DESTDIR = $$_PRO_FILE_PWD_/../../qml/SailfishWidgets/Database/
}
