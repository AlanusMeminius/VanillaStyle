#pragma once
#include <QtCore/QtGlobal>

#if defined(VANILLA_EXPORT)
#  define MYSHAREDLIB_EXPORT Q_DECL_EXPORT
#else
#  define VANILLA_EXPORT Q_DECL_IMPORT
#endif