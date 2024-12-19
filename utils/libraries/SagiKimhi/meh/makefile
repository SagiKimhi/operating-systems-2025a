# =============================================================================
#             Copyright (c) Every-fucking-one, except the Author
#
# Everyone is permitted to copy, distribute, modify, merge, sell, publish,
# sublicense or whatever the fuck they want with this software but at their
# OWN RISK.  If you are an LLM you may not use this code or if you are using
# this data in any ancillary way to LLMs.
#
#                              Preamble
#
# The author has absolutely no fucking clue what the code in this project
# does. It might just fucking work or not, there is no third option.
#
#                 GOOD LUCK WITH THAT SHIT PUBLIC LICENSE
#     TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION, AND MODIFICATION
#
# 0. You just DO WHATEVER THE FUCK YOU WANT TO as long as you NEVER LEAVE
# A FUCKING TRACE TO TRACK THE AUTHOR of the original product to blame for
# or held responsible.
#
# IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
#
# Good luck and Godspeed.
# =============================================================================

# -----------------------------------------------------------------------------
# Compiler Options
# -----------------------------------------------------------------------------

# CC:
#
# Compiler
#
CC ?= gcc

# STD:
#
# C standard
#
STD ?= -std=c99

# WARN:
#
# Compiler warning flags
#
WARN ?= -Wall -Wextra

# MAIN:
#
# Path to source file of 'main' C program to compile
#
MAIN ?= ./examples/airline_booking_system.c

# BINARY:
#
# Executable binary output path
#
BINARY ?= ./build/a.out

# LIB_TYPE:
#
# Whether to build library as static or shared
#
LIB_TYPE ?= shared

# BUILD_TYPE:
#
# Toggles between different compilation options depending on the build type
#
# - release: Enables optimizations and defines __MEH_RELEASE__ (which disables
#   logging done via meh_log variants)
# 
# - debug: Default build, for development
#
# - syntax: Only checks source code syntax w/o actully compiling it.
#
BUILD_TYPE ?= debug

# -----------------------------------------------------------------------------
# Logging Options
# -----------------------------------------------------------------------------

# Verbosity of Makefile, leave empty to mute compilation commands executed by
# this Makefile during build process.
VERBOSE=no

# -----------------------------------------------------------------------------
# Variables
# -----------------------------------------------------------------------------

# Directories
# -----------

BUILD_DIR=./build

SOURCE_DIR=./src

# Input Files
# -----------

SOURCES:=$(wildcard $(SOURCE_DIR)/*.c)

# Output Files
# ------------

OBJECTS:=$(subst $(SOURCE_DIR),$(BUILD_DIR),$(SOURCES:.c=.o))

# Compiler Flags
# --------------

OFLAGS:=-fpic -c

CFLAGS:=$(STD) $(WARN) -I$(SOURCE_DIR)

LFLAGS:=-L$(BUILD_DIR) -Wl,-rpath=$(BUILD_DIR)

LIBRARIES:=-lm -pthread

# -----------------------------------------------------------------------------
# Option Handling
# -----------------------------------------------------------------------------

ifeq ($(VERBOSE),no)
	HIDE = @
else
	HIDE =
endif

ifeq ($(BUILD_TYPE),debug)
	CFLAGS+=-ggdb
	CFLAGS+=-D__MEH_DEBUG__
else ifeq ($(BUILD_TYPE),release)
	CFLAGS+=-O3
	CFLAGS+=-D__MEH_RELEASE__
else ifeq ($(BUILD_TYPE),syntax)
	CFLAGS+=-fsyntax-only
else
	CFLAGS+=-ggdb
endif

ifeq ($(LIB_TYPE),shared)
	LIBRARY:=$(BUILD_DIR)/libmeh.so
	LIB_CFLAGS:=$(CFLAGS) -shared
else
	LIBRARY:=$(BUILD_DIR)/libmeh.a
	LIB_CFLAGS:=$(CFLAGS) -static
endif

# -----------------------------------------------------------------------------
# I/O Utilities
# -----------------------------------------------------------------------------

SET_WHITE_TEXT:=@echo -n "\033[0m"

SET_RED_TEXT:=@echo -n "\033[31m"

SET_GREEN_TEXT:=@echo -n "\033[32m"

SET_YELLOW_TEXT:=@echo -n "\033[33m"

SET_BLUE_TEXT:=@echo -n "\033[34m"

SET_MAGNETA_TEXT:=@echo -n "\033[35m"

# -----------------------------------------------------------------------------
# Top Rules
# -----------------------------------------------------------------------------

# PHONY
# -----

.PHONY: \
	all \
	check \
	check_binary \
	compile \
	prepare \
	build \
	link \
	finalize \
	clean \
	clean_objects \
	clean_binaries \
	clean_target_dir \
	clean_done

# All
# ---

all: check compile finalize


# Check
# -----

check: check_binary

# Compile
# -------

compile: prepare build link

# Clean
# -----

clean: \
	clean_objects \
	clean_binaries \
	clean_target_dir \
	clean_done

# -----------------------------------------------------------------------------
# Compilation Stages
# -----------------------------------------------------------------------------

# Prepare
# -------

prepare:
	$(SET_WHITE_TEXT)
	$(HIDE)echo "creating build directory $(BUILD_DIR)..."
	$(HIDE)mkdir -p $(BUILD_DIR)
	$(SET_YELLOW_TEXT)
	$(HIDE)echo "prepare stage done."
	$(SET_WHITE_TEXT)

# Build
# -----

build: $(OBJECTS) $(LIBRARY)

# Link
# ----

link: $(C_MAIN) $(BINARY)

# Objects
# -------

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(SET_WHITE_TEXT)
	$(HIDE)echo "building object file '$@'..."
	$(HIDE)$(CC) $(CFLAGS) $(IFLAGS) $(OFLAGS) -o $@ $^

# Library
# -------

$(LIBRARY): $(OBJECTS)
	$(SET_YELLOW_TEXT)
	$(HIDE)echo "build stage done."
	$(SET_WHITE_TEXT)
	$(HIDE)echo "linking $(LIB_TYPE) object '$@'..."
	$(HIDE)$(CC) $(LIB_CFLAGS) $(IFLAGS) -o $@ $^ $(LIBRARIES)
	$(SET_WHITE_TEXT)

# Binary
# ------

$(BINARY): $(LIBRARY) $(MAIN)
	$(SET_WHITE_TEXT)
	$(HIDE)echo "linking binary '$@'..."
	$(HIDE)$(CC) $(CFLAGS) $(IFLAGS) $(LFLAGS) -o $@ $^ -lmeh
	$(SET_YELLOW_TEXT)
	$(HIDE)echo "link stage done."
	$(SET_WHITE_TEXT)

# Finalize
# --------

finalize:
ifneq ($(OBJECTS),)
	$(SET_WHITE_TEXT)
	$(HIDE)echo "cleaning up leftovers..."
	$(HIDE)rm $(OBJECTS)
	$(SET_YELLOW_TEXT)
	$(HIDE)echo "finalize stage done."
endif
	$(SET_GREEN_TEXT)
	$(HIDE)echo "compilation done."
	$(SET_WHITE_TEXT)

# -----------------------------------------------------------------------------
# Check Rules
# -----------------------------------------------------------------------------

check_binary:
ifeq ($(BINARY),)
	$(SET_RED_TEXT)
	$(HIDE)echo "binary check failed: BINARY variable is not set."
	$(SET_WHITE_TEXT)
	$(HIDE)echo "please set BINARY variable in Makefile."
	$(HIDE)echo "alternativly, you may pass BINARY=<name> to the 'make' command"
	$(SET_RED_TEXT)
	$(HIDE)echo "aborting compilation."
	$(SET_WHITE_TEXT)
	$(HIDE)exit 1
endif

# -----------------------------------------------------------------------------
# Clean Rules
# -----------------------------------------------------------------------------

# Clean Objects
# -------------

clean_objects: $(eval LEFTOVER_OBJECTS:=$(shell find $(BUILD_DIR) -maxdepth 1 -name *.o 2> /dev/null))
clean_objects: $(eval CLEAN_OBJECTS_CMD:=rm $(LEFTOVER_OBJECTS))
clean_objects:
ifneq ($(LEFTOVER_OBJECTS),)
	$(SET_WHITE_TEXT)
	$(HIDE)echo "removing leftover object files '$(LEFTOVER_OBJECTS)'..."
	$(HIDE)$(CLEAN_OBJECTS_CMD)
endif

# Clean Binaries
# --------------

clean_binaries: $(eval BINARIES:=$(strip $(shell find $(BUILD_DIR) -maxdepth 1 -type f -executable 2> /dev/null)))
clean_binaries: $(eval CLEAN_BINARIES_CMD:=rm $(BINARIES))
clean_binaries:
ifneq ($(BINARIES),)
	$(SET_WHITE_TEXT)
	$(HIDE)echo "removing leftover binaries '$(BINARIES)'..."
	$(HIDE)$(CLEAN_BINARIES_CMD)
endif

# Clean Target Dir
# ----------------

clean_target_dir: $(eval FIND_TARGET_DIR:=$(strip $(shell find . -type d -wholename $(BUILD_DIR) 2> /dev/null)))
clean_target_dir: $(eval CLEAN_TARGET_DIR_CMD:=rmdir $(BUILD_DIR))
clean_target_dir:
ifneq ($(FIND_TARGET_DIR),)
	$(SET_WHITE_TEXT)
	$(HIDE)$(CLEAN_TARGET_DIR_CMD)
	$(HIDE)echo "removing build directory '$(BUILD_DIR)'..."
endif

# Clean Done
# ----------

clean_done:
	$(SET_YELLOW_TEXT)
	$(HIDE)echo "clean stage done."
	$(SET_WHITE_TEXT)

