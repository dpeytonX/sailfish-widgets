include($$PWD/../applicationsettings/applicationsettings.pro)
include($$PWD/../language/language.pro)

QT       -= gui
CONFIG += sailfishapp

TARGET = core
TEMPLATE = lib

DEFINES += SAILFISHMAIN_LIBRARY

SOURCES += sailfishmain.cpp

HEADERS += sailfishmain.h\
        sailfishmain_global.h

INCLUDEPATH += $$PWD/../applicationsettings $$PWD/../language

unix {
    target.path = $$installPath
    INSTALLS += target
}
