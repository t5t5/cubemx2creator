include(../../../qpe-c2c-include.pri)

QT += core testlib
QT -= gui

CONFIG += c++17

TARGET = test_makefile
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

MOC_DIR = ./tmp/moc
OBJECTS_DIR = ./tmp/obj
RCC_DIR = ./tmp/rcc
UI_DIR = ./tmp/ui
DESTDIR = $$QPE_C2C_BUILD_TEST_DIR

LIBS += -L$$QPE_CORE_BUILD_DIR -lqpecore
LIBS += -L$$QPE_C2C_BUILD_DIR -lqpe-c2c

SOURCES += \
    test_makefile.cpp
