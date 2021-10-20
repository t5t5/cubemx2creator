include(../../qpe-c2c-include.pri)

QT += core
QT -= gui

CONFIG += c++14

TARGET = qpe-c2c
TEMPLATE = lib
CONFIG += $$QPE_C2C_CONFIG_STATICLIB

DEFINES += QPE_C2C_LIB

MOC_DIR = ./tmp/moc
OBJECTS_DIR = ./tmp/obj
RCC_DIR = ./tmp/rcc
UI_DIR = ./tmp/ui
DESTDIR = $$QPE_C2C_BUILD_DIR

LIBS += -L$$QPE_CORE_BUILD_DIR -lqpecore

include(global/global.pri)
include(makefile/makefile.pri)