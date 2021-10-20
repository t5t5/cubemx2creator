!isEmpty(QPE_C2C_INCLUDE_PRI_INCLUDED):error(qpe-c2c-include.pri already included)
QPE_C2C_INCLUDE_PRI_INCLUDED = 1

include(3rdparty/qpe/qpe/qpe-include.pri)

# пути к исходникам и результирующей сборке
isEmpty(QPE_C2C_SRC_DIR):QPE_C2C_SRC_DIR = $$PWD
isEmpty(QPE_C2C_BUILD_DIR):QPE_C2C_BUILD_DIR = $$shadowed($$PWD)

QPE_C2C_SRC_DIR = $$PWD

QPE_C2C_BUILD_TEST_DIR = $$QPE_C2C_BUILD_DIR/tests

# определения для статичной сборки qpe-c2c
contains(DEFINES, QPE_C2C_LIB_STATIC) {
    QPE_C2C_BUILD_DIR = $$QPE_C2C_BUILD_DIR/lib
    QPE_C2C_CONFIG_STATICLIB = staticlib
    QPE_C2C_CONFIG_ADDON_LIBS =
} else {
    QPE_C2C_BUILD_DIR = $$QPE_C2C_BUILD_DIR
    QPE_C2C_CONFIG_STATICLIB =
    QPE_C2C_CONFIG_ADDON_LIBS =
}

INCLUDEPATH += $$QPE_C2C_SRC_DIR/include

# qpe
INCLUDEPATH += $QPE_SRC_DIR/include
