#ifndef C2C_GLOBAL_H
#define C2C_GLOBAL_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <Qpe/Qpe>

#if defined(QPE_C2C_LIB_STATIC)
#  define QPE_C2C_EXPORT
#else
#  if defined(QPE_C2C_LIB)
#    define QPE_C2C_EXPORT Q_DECL_EXPORT
#  else
#    define QPE_C2C_EXPORT Q_DECL_IMPORT
#  endif
#endif

#endif // C2C_GLOBAL_H
