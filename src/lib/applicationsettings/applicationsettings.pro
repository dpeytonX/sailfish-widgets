TEMPLATE = lib
TARGET = applicationsettings
QT += qml quick
CONFIG += qt plugin

#QMAKE_CXXFLAGS += "-std=c++0x"

TARGET = $$qtLibraryTarget($$TARGET)
uri = SailfishWidgets.Settings

DEFINES += APPLICATIONSETTINGS_LIBRARY

# Input
SOURCES += \
    applicationsettings_plugin.cpp \
    applicationsettings.cpp \
    qmlpropertywrapper.cpp

HEADERS += \
    applicationsettings_plugin.h \
    applicationsettings.h \
    qmlpropertywrapper.h

OTHER_FILES = qmldir

!contains( CONFIG, "DEBUG") {
    strip_lib.target = strlib
    strip_lib.depends = all
    strip_lib.commands = $(STRIP) --strip-all $(TARGET)
    QMAKE_EXTRA_TARGETS += strip_lib
}

contains( CMD_LINE, "true") {
 !equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/../../qml/SailfishWidgets/Settings/qmldir
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

isEmpty( CMD_LINE) {
  DESTDIR = $$_PRO_FILE_PWD_/../../qml/SailfishWidgets/Settings/
}
