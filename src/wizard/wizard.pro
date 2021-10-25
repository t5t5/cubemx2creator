include(../../qpe-c2c-include.pri)

QT += core gui widgets $$QPE_C2C_CONFIG_ADDON_LIBS

CONFIG += c++17

TARGET = wizard
CONFIG -= app_bundle

TEMPLATE = app

MOC_DIR = ./tmp/moc
OBJECTS_DIR = ./tmp/obj
RCC_DIR = ./tmp/rcc
UI_DIR = ./tmp/ui
DESTDIR = $$QPE_C2C_BUILD_DIR

LIBS += -L$$QPE_C2C_BUILD_DIR -lqpe-c2c

SOURCES += \
    cubemx2creatorwizard.cpp \
    main.cpp \
    wpage_selectcubemxproject.cpp

HEADERS += \
    cubemx2creatorwizard.h \
    wpage_selectcubemxproject.h \
    wpage_selectcubemxproject_p.h

FORMS += \
    wpage_selectcubemxproject.ui
