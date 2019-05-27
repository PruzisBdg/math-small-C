# --------------------------------------------------------------------------
#
# Arithmetic Library: TDD Unit Tests, common defs.
#
# ---------------------------------------------------------------------------

# Import TDD harness defs
include ../../../unity_tdd/tdd_common_pre_build.mak

# (Additional) compiler flags
CFLAGS := $(CFLAGS) -D__COMPILER_IS_GENERIC__ -D__SYSTEM_IS_ANY__ -D__TOOL_IS_X86_GCC__

# Source files to be tested are here.
SRCDIR = ../../$(TARGET_BASE_DIR)/

# All math tests reference these unnder /math/.
INC_DIRS := $(INC_DIRS) -I. -I../../arith_incl -I../../tiny2_public

# --------------------------------- eof ------------------------------------


