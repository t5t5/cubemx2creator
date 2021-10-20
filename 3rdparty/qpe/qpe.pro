TEMPLATE = subdirs

QPE_DIRS  = qpe_include
QPE_DIRS += qpe_core
QPE_DIRS += qpe_logger
QPE_DIRS += qpe_tests


qpe_include.subdir = qpe/include

qpe_core.subdir = qpe/src/core
qpe_core.depends = qpe_include

qpe_logger.subdir = qpe/src/logger
qpe_logger.depends = qpe_core

qpe_tests.subdir = qpe/src/tests
qpe_tests.depends = qpe_core qpe_logger


SUBDIRS += $$QPE_DIRS
