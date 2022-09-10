!isEmpty(QPYTHON_DOCX_PRI_INCLUDED) {
    error("QtPythonDocx.pri already included")
}
QPYTHON_DOCX_PRI_INCLUDED = 1

QPYTHON_DOCX_VERSION_STR = 0.0.1
QPYTHON_DOCX_VERSION = 0x000001
VERSION = $$QPYTHON_DOCX_VERSION_STR
QPYTHON_DOCX_COPYRIGHT_YEAR = 2022

CONFIG += c++14

# Avoid automatically appending version numbers to generated libraries
CONFIG += skip_target_version_ext

# Config Para
CONFIG(debug, debug|release):{
    FILE_POSTFIX = d
    DIR_COMPILEMODE = Debug
}
else:CONFIG(release, debug|release):{
    FILE_POSTFIX =
    DIR_COMPILEMODE = Release
}

win32:{
    CONFIG(MinGW, MinGW|MinGW32|MinGW64|MSVC|MSVC32|MSVC64):{
            DIR_COMPILER = MinGW32
            DIR_PLATFORM = Win32
            FILE_LIB_PREFIX = lib
            FILE_LIB_EXT = .a
    }
    else:CONFIG(MinGW64, MinGW|MinGW32|MinGW64|MSVC|MSVC32|MSVC64):{
            DIR_COMPILER = MinGW64
            DIR_PLATFORM = Win64
            FILE_LIB_PREFIX =lib
            FILE_LIB_EXT = .a
    }
    else:CONFIG(MSVC64, MinGW|MinGW32|MinGW64|MSVC|MSVC32|MSVC64):{
            DIR_COMPILER = MSVC64
            DIR_PLATFORM = Win64
            FILE_LIB_PREFIX =
            FILE_LIB_EXT = .lib
    }

    FILE_DLL_PREFIX =
    FILE_DLL_EXT = .dll
}
else:mac:{
    DIR_PLATFORM = MAC
    FILE_LIB_PREFIX = lib
    FILE_LIB_EXT = .a
    FILE_DLL_PREFIX = lib
    FILE_DLL_EXT = .so
}
else:ios:{
    DIR_COMPILER = LLVM
    DIR_PLATFORM = IOS
    FILE_LIB_PREFIX = lib
    FILE_LIB_EXT = .a
    FILE_DLL_PREFIX = lib
    FILE_DLL_EXT = .so
}
else:linux:{
    CONFIG(GCC, GCC|GCC32|GCC64):{
        DIR_COMPILER = GCC32
        DIR_PLATFORM = Linux32
    }
    else:CONFIG(GCC64, GCC|GCC32|GCC64):{
        DIR_COMPILER = GCC64
        DIR_PLATFORM = Linux64
    }

    FILE_LIB_PREFIX = lib
    FILE_LIB_EXT = .a
    FILE_DLL_PREFIX = lib
    FILE_DLL_EXT = .so
}
else:android:{
    CONFIG(X86_GCC_4.8, X86_GCC_4.4.3|X86_GCC_4.6|X86_GCC_4.7|X86_GCC_4.8):{
          DIR_COMPILER = X86_GCC_4.8
          DIR_PLATFORM = Android
          FILE_LIB_PREFIX = lib
          FILE_LIB_EXT = .a
          FILE_DLL_PREFIX = lib
          FILE_DLL_EXT = .so
    }
}

msvc {
    #Don't warn about sprintf, fopen etc being 'unsafe'
    DEFINES += _CRT_SECURE_NO_WARNINGS
    QMAKE_CXXFLAGS_WARN_ON *= -w44996
    # Speed up startup time when debugging with cdb
    QMAKE_LFLAGS_DEBUG += /INCREMENTAL:NO
}


equals(TEST, 1) {
    QT +=testlib
    DEFINES += WITH_TESTS
}

IDE_APP_NAME = QPYTHON
IDE_APP_PATH = $$PWD/bin
QPYTHON_DOCX_PREFIX = $$IDE_APP_PATH/$$DIR_PLATFORM/$$DIR_COMPILER/$$DIR_COMPILEMODE
IDE_BIN_PATH     = $$QPYTHON_DOCX_PREFIX
IDE_LIBRARY_PATH = $$QPYTHON_DOCX_PREFIX
IDE_PLUGIN_PATH  = $$QPYTHON_DOCX_PREFIX/plugins
IDE_DOC_PATH     = $$QPYTHON_DOCX_PREFIX/share/doc
IDE_DATA_PATH    = $$QPYTHON_DOCX_PREFIX/share/$$IDE_APP_NAME

DEFINES += $$shell_quote(IDE_BIN_PATH=\"$$IDE_BIN_PATH\")
DEFINES += $$shell_quote(IDE_LIBRARY_PATH=\"$$IDE_LIBRARY_PATH\")
DEFINES += $$shell_quote(IDE_PLUGIN_PATH=\"$$IDE_PLUGIN_PATH\")

QPYTHON_DOCX_PATH_INFO = 0
equals(QPYTHON_DOCX_PATH_INFO, 1) {
message("=================PATH info =============================")
message("IDE_LIBRARY_PATH:       " $$IDE_LIBRARY_PATH)
message("IDE_PLUGIN_PATH:        " $$IDE_PLUGIN_PATH)
message("IDE_DATA_PATH:          " $$IDE_DATA_PATH)
message("IDE_DOC_PATH:           " $$IDE_DOC_PATH)
message("IDE_BIN_PATH:           " $$IDE_BIN_PATH)
message("INSTALL_LIBRARY_PATH:   " $$INSTALL_LIBRARY_PATH)
message("INSTALL_PLUGIN_PATH:    " $$INSTALL_PLUGIN_PATH)
message("INSTALL_LIBEXEC_PATH:   " $$INSTALL_LIBEXEC_PATH)
message("INSTALL_BIN_PATH:       " $$INSTALL_BIN_PATH)
message("INSTALL_APP_PATH:       " $$INSTALL_APP_PATH)
message("==============================================")
}

defineTest(minQtVersion) {
    maj = $$1
    min = $$2
    patch = $$3
    isEqual(QT_MAJOR_VERSION, $$maj) {
        isEqual(QT_MINOR_VERSION, $$min) {
            isEqual(QT_PATCH_VERSION, $$patch) {
                return(true)
            }
            greaterThan(QT_PATCH_VERSION, $$patch) {
                return(true)
            }
        }
        greaterThan(QT_MINOR_VERSION, $$min) {
            return(true)
        }
    }
    greaterThan(QT_MAJOR_VERSION, $$maj) {
        return(true)
    }
    return(false)
}
