include($$PWD/../QtPythonDocx.pri)

PYTHON_VERSION=310
PYTHON_PATH=$$PWD/../3rdparty/Python$${PYTHON_VERSION}

QT = core

TEMPLATE = lib
DESTDIR = $${IDE_APP_PATH}
TARGET	 = PYSDK$${FILE_POSTFIX}
DEFINES *= KPYSDK_LIBRARY

INCLUDEPATH +=$${PYTHON_PATH}/include

SOURCES += \
    $$PWD/KPYSDK.cpp

HEADERS += \
    $$PWD/KPYSDK.h

LIBS += -L$${PYTHON_PATH}/libs -lpython$${PYTHON_VERSION}