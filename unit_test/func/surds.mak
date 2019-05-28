# ------------------------------------------------------------------
#
# TDD makefile WordList lib
#
# ---------------------------------------------------------------------

# Code folder, test folder and test file all get same name.
TARGET_BASE = surds
TARGET_BASE_DIR = func/src/$(TARGET_BASE)

# Defs common to the utils.
include ../math_common_pre.mak

# Include Unity double support for these floating point tests.
CFLAGS := $(CFLAGS) -DUNITY_INCLUDE_DOUBLE

# The complete files list
SRC_FILES := $(SRC_FILES) $(UNITYDIR)unity.c \
								$(SRCDIR)InvSqrtFP.c \
								$(HARNESS_TESTS_SRC) $(HARNESS_MAIN_SRC) $(LIBS)

# Clean and build
include ../math_common_build.mak

# ------------------------------- eof ------------------------------------

