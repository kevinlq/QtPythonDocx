include($$PWD/../QtPythonDocx.pri)

QT = core gui widgets

TEMPLATE = app
DESTDIR = $$IDE_APP_PATH

INCLUDEPATH +=$$PWD/../src/

SOURCES += \
    MainWidget.cpp \
    WordItemData.cpp \
    main.cpp

HEADERS += \
    MainWidget.h \
    WordItemData.h

LIBS += -L$${IDE_APP_PATH}/ -lPYSDK$${FILE_POSTFIX}
