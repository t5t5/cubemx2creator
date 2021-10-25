TEMPLATE = subdirs

SUBDIRS += c2c
SUBDIRS += tests
SUBDIRS += wizard

tests.depends = c2c
wizard.depends = c2c
