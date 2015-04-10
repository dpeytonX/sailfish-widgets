QT = qml quick

QMAKE_CXXFLAGS += "-std=c++0x"

TARGET = core
TEMPLATE = lib

DEFINES += SAILFISHMAIN_LIBRARY

SOURCES += sailfishmain.cpp

HEADERS += sailfishmain.h \
        sailfishmain_global.h

INCLUDEPATH += $$PWD/../applicationsettings /usr/include/sailfishapp

unix {
    target.path = $$installPath
    INSTALLS += target
}

unix:!macx: LIBS += -L$$OUT_PWD/../../applicationsettings/i486 \
                    -L$$OUT_PWD/../../applicationsettings/armv -lapplicationsettings

INCLUDEPATH += $$PWD/../applicationsettings
DEPENDPATH += $$PWD/../applicationsettings
