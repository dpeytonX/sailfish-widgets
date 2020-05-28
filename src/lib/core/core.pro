QT = qml quick

QMAKE_CXXFLAGS += "-std=c++0x"

TARGET = core
TEMPLATE = lib

DEFINES += SAILFISHMAIN_LIBRARY

SOURCES += sailfishmain.cpp

INCLUDEPATH += /usr/include/sailfishapp

HEADERS += sailfishmain.h \
        sailfishmain_global.h \
       $$PWD/../applicationsettings/applicationsettings.h \


LIBS += -L/usr/lib -lsailfishapp

unix:!macx: LIBS += -L$$OUT_PWD/../../applicationsettings/i486 \
                    -L$$OUT_PWD/../../applicationsettings/armv7hl \
                    -lapplicationsettings

INCLUDEPATH += $$PWD/../applicationsettings
DEPENDPATH += $$PWD/../applicationsettings

!contains( CONFIG, "DEBUG") {
    strip_lib.target = strlib
    strip_lib.depends = all
    strip_lib.commands = $(STRIP) --strip-all $(TARGET)
    QMAKE_EXTRA_TARGETS += strip_lib
}
