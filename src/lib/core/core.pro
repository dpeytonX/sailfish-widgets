QT = qml quick

QMAKE_CXXFLAGS += "-std=c++0x"

TARGET = core
TEMPLATE = lib

DEFINES += SAILFISHMAIN_LIBRARY

SOURCES += sailfishmain.cpp

HEADERS += sailfishmain.h \
        sailfishmain_global.h

INCLUDEPATH += $$PWD/../applicationsettings /usr/include/sailfishapp

LIBS += -L/usr/lib -lsailfishapp

unix:!macx: LIBS += -L$$OUT_PWD/../../applicationsettings/i486 \
                    -L$$OUT_PWD/../../applicationsettings/armv

INCLUDEPATH += $$PWD/../applicationsettings
DEPENDPATH += $$PWD/../applicationsettings

!contains( CONFIG, "DEBUG") {
    strip_lib.target = strlib
    strip_lib.depends = all
    strip_lib.commands = $(STRIP) --strip-all $(TARGET)
    QMAKE_EXTRA_TARGETS += strip_lib
}
