#pragma once

#include <QtCore/qglobal.h>

#if defined(KPYSDK_LIBRARY)
#  define KPYSDK_EXPORT Q_DECL_EXPORT
#else
#  define KPYSDK_EXPORT Q_DECL_IMPORT
#endif
