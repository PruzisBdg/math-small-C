# ------------------------------------------------------------------
#
# TDD makefile WordList lib
#
# ---------------------------------------------------------------------

# Code folder, test folder and test file all get same name.
TARGET_BASE = float
TARGET_BASE_DIR = arith/src/$(TARGET_BASE)

# Defs common to the utils.
include ../math_common_pre.mak

# The complete files list
SRC_FILES := $(SRC_FILES) $(UNITYDIR)unity.c \
								$(SRCDIR)Get_pwr10_float.c \
								$(HARNESS_TESTS_SRC) $(HARNESS_MAIN_SRC) $(LIBS)

# Clean and build
include ../math_common_build.mak

# ------------------------------- eof ------------------------------------

