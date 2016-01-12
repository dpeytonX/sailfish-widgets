TEMPLATE = lib
TARGET = language
QT += qml quick
CONFIG += qt plugin

QMAKE_CXXFLAGS += "-std=c++0x"

INCLUDEPATH += /usr/include/sailfishapp

LIBS += -L/usr/lib -lsailfishapp

TARGET = $$qtLibraryTarget($$TARGET)
uri = SailfishWidgets.Language

# Input
SOURCES += \
    language_plugin.cpp \
    localeitem.cpp \
    defaultlocale.cpp \
    installedlocales.cpp

HEADERS += \
    language_plugin.h \
    localeitem.h \
    defaultlocale.h \
    installedlocales.h

OTHER_FILES = qmldir

contains( CMD_LINE, "true") {
!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/../../qml/SailfishWidgets/Language/qmldir
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

lg.depends = $$OUT_PWD/liblanguage.so
lg.target = $$_PRO_FILE_PWD_/../../qml/SailfishWidgets/Language/
lg.commands = $(COPY_FILE) $$lg.depends $$lg.target
QMAKE_EXTRA_TARGETS += lg
PRE_TARGETDEPS += $$lg.target
