include($$PWD/QtPythonDocx.pri)

#version check qt
!minQtVersion(5, 11, 0) {
    message("Cannot build Qt SDK with Qt version $${QT_VERSION}.")
    error("Use at least Qt 5.11.0")
}

PYTHON_PATH=$$PWD/Python310

QT = core gui widgets

TEMPLATE = app
DESTDIR = $$IDE_APP_PATH

INCLUDEPATH +=$${PYTHON_PATH}/include

SOURCES += \
    KPythonRunScript.cpp \
    MainWidget.cpp \
    main.cpp

HEADERS += \
    KPythonRunScript.h \
    MainWidget.h

LIBS += -L$${PYTHON_PATH}/libs -lpython310

DISTFILES += \
    bin/script/wordOperate.py
