TEMPLATE = subdirs

include($$PWD/QtPythonDocx.pri)

#version check qt
!minQtVersion(5, 11, 0) {
    message("Cannot build Qt SDK with Qt version $${QT_VERSION}.")
    error("Use at least Qt 5.11.0")
}

SUBDIRS += \
    $$PWD/src \
    $$PWD/examples

CONFIG	+=ordered
