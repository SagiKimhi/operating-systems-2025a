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
# Files and Directories
# -----------------------------------------------------------------------------

BINARY=a.out

TARGET_DIR=./build

SOURCE_DIR=./src

TARGET:=$(TARGET_DIR)/$(BINARY)

SOURCES:=$(wildcard $(SOURCE_DIR)/*.c)

OBJECTS:=$(subst $(SOURCE_DIR),$(TARGET_DIR),$(SOURCES:.c=.o))

# -----------------------------------------------------------------------------
# Compiler and Flags
# -----------------------------------------------------------------------------

# Compiler
CC=gcc

# Compilation Flags
CFLAGS:=-ansi -pedantic -Wall -Wextra -I$(SOURCE_DIR)

# -----------------------------------------------------------------------------
# Utils
# -----------------------------------------------------------------------------

SET_WHITE_TEXT:=@echo -n "\033[0m" # White text for "printf"

SET_RED_TEXT:=@echo -n "\033[31m" # Red text for "printf"

SET_GREEN_TEXT:=@echo -n "\033[32m" # Green text for "printf"

SET_YELLOW_TEXT:=@echo -n "\033[33m" # Yellow text for "printf"

SET_BLUE_TEXT:=@echo -n "\033[34m" # Blue text for "printf"

SET_MAGNETA_TEXT:=@echo -n "\033[35m" # Magneta text for "printf"

# -----------------------------------------------------------------------------
# Top Level Rules
# -----------------------------------------------------------------------------

.PHONY: \
	all \
	check \
	check_binary \
	compile \
	create_build_dir \
	build_and_link \
	post_compilation_cleanup \
	compilation_done \
	clean \
	clean_objects \
	clean_binaries \
	clean_target_dir \
	clean_done

all: \
	check \
	compile

check: \
	check_binary

compile: \
	create_build_dir \
	build_and_link \
	post_compilation_cleanup \
	compilation_done

clean: \
	clean_objects \
	clean_binaries \
	clean_target_dir \
	clean_done

# -----------------------------------------------------------------------------
# Check Rules
# -----------------------------------------------------------------------------

check_binary:
ifeq ($(BINARY),)
	$(SET_RED_TEXT)
	@echo "Binary Check Failed: BINARY variable is not set."
	$(SET_YELLOW_TEXT)
	@echo "Please set BINARY variable in Makefile."
	@echo "Alternativly, you may pass BINARY=<name> to the 'make' command"
	$(SET_RED_TEXT)
	@echo "Aborting compilation."
	$(SET_WHITE_TEXT)
	@exit 1
endif

# -----------------------------------------------------------------------------
# Compilation Rules
# -----------------------------------------------------------------------------

create_build_dir:
	@mkdir -p $(TARGET_DIR)

build_and_link: \
	$(OBJECTS) \
	$(TARGET)

$(TARGET): $(OBJECTS)
	$(SET_YELLOW_TEXT)
	@echo "$(BINARY): Linking $@..."
	$(SET_WHITE_TEXT)
	@$(CC) $(CFLAGS) -o $@ $^

$(TARGET_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(SET_YELLOW_TEXT)
	@echo "$(BINARY): Building $@..."
	$(SET_WHITE_TEXT)
	@$(CC) $(CFLAGS) -c -o $@ $^

post_compilation_cleanup:
	$(SET_YELLOW_TEXT)
	@echo "$(BINARY): Cleaning up leftovers..."
	$(SET_WHITE_TEXT)
	@rm $(OBJECTS)

compilation_done:
	$(SET_GREEN_TEXT)
	@echo "$(BINARY): Build Done. (built to '$(TARGET)')"
	$(SET_WHITE_TEXT)

# -----------------------------------------------------------------------------
# Clean Rules
# -----------------------------------------------------------------------------

clean_objects: $(eval LEFTOVER_OBJECTS:=$(shell find $(TARGET_DIR) -maxdepth 1 -name *.o 2> /dev/null))
clean_objects: $(eval CLEAN_OBJECTS_CMD:=rm $(LEFTOVER_OBJECTS))
clean_objects:
ifneq ($(LEFTOVER_OBJECTS),)
	$(SET_YELLOW_TEXT)
	@echo "clean: Cleaning Objects... ($(CLEAN_OBJECTS_CMD))"
	@$(CLEAN_OBJECTS_CMD)
	$(SET_WHITE_TEXT)
endif

clean_binaries: $(eval LEFTOVER_BINARIES:=$(strip $(shell find $(TARGET_DIR) -maxdepth 1 -type f -executable 2> /dev/null)))
clean_binaries: $(eval CLEAN_BINARIES_CMD:=rm $(LEFTOVER_BINARIES))
clean_binaries:
ifneq ($(LEFTOVER_BINARIES),)
	$(SET_YELLOW_TEXT)
	@echo "clean: Cleaning Binaries... ($(CLEAN_BINARIES_CMD))"
	@$(CLEAN_BINARIES_CMD)
	$(SET_WHITE_TEXT)
endif

clean_target_dir: $(eval FIND_TARGET_DIR:=$(strip $(shell find . -type d -wholename $(TARGET_DIR) 2> /dev/null)))
clean_target_dir: $(eval CLEAN_TARGET_DIR_CMD:=rmdir $(TARGET_DIR))
clean_target_dir:
ifneq ($(FIND_TARGET_DIR),)
	$(SET_YELLOW_TEXT)
	@echo "clean: Cleaning Build Directory... ($(CLEAN_TARGET_DIR_CMD))"
	@$(CLEAN_TARGET_DIR_CMD)
	$(SET_WHITE_TEXT)
endif

clean_done:
	$(SET_GREEN_TEXT)
	@echo "clean: Clean Done."
	$(SET_WHITE_TEXT)

# -----------------------------------------------------------------------------
# Clean Utils
# -----------------------------------------------------------------------------

# -----------------------------------------
# If we'd like to prompt prior to deletion:
# -----------------------------------------
#
# ifneq ($(LEFTOVER_BINARIES),)
# 	@echo "make clean wants to execute the following command:"
# 	$(SET_YELLOW_TEXT)
# 	@echo "$(CLEAN_BINARIES_CMD)"
# 	$(SET_WHITE_TEXT)
# 	@echo -n "Do you accept? [y/n] " && read ans && [ $${ans:-N} = y ]
# 	@$(CLEAN_BINARIES_CMD)
# endif
#
# -----------------------------------------
