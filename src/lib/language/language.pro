TEMPLATE = lib
TARGET = language
QT += qml quick
CONFIG += qt plugin

QMAKE_CXXFLAGS += "-std=c++0x"

TARGET = $$qtLibraryTarget($$TARGET)
uri = SailfishWidgets.Language

# Input
SOURCES += \
    language_plugin.cpp \
    #applicationsettings.cpp \
    locale.cpp

HEADERS += \
    language_plugin.h \
    #applicationsettings.h \
    locale.h

OTHER_FILES = qmldir

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

