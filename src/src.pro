TEMPLATE = subdirs

SUBDIRS += c2c
SUBDIRS += tests

tests.depends = c2c
