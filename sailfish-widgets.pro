#-------------------------------------------------
#
# Project created by QtCreator 2016-01-11T22:18:36
#
#-------------------------------------------------


TEMPLATE=subdirs
SUBDIRS = src/lib/applicationsettings \
          src/lib/core \
          src/lib/database \
          src/lib/filemanagement \
          src/lib/language

OTHER_FILES += src/qml/SailfishWidgets/Components/* \
               src/qml/SailfishWidgets/Database/* \
               src/qml/SailfishWidgets/FileManagement/* \
               src/qml/SailfishWidgets/JS/* \
               src/qml/SailfishWidgets/Language/* \
               src/qml/SailfishWidgets/Settings/* \
               src/qml/SailfishWidgets/Utilities/*
