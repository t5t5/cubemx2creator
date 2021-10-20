TEMPLATE = subdirs

TARGET = cubemx2creator

SUBDIRS += 3rdparty
SUBDIRS += include
SUBDIRS += src

include.depends = 3rdparty
src.depends = 3rdparty include


OTHER_FILES += \
    .gitignore \
    .qmake.conf \
    qpe-c2c-include.pri \
    README.md
