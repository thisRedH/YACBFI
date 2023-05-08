# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -g3 -std=c99 -O0 -I$(INC_DIR) -MP -MD
RELEASE_CFLAGS = -s -fomit-frame-pointer -fdata-sections -ffunction-sections -DNDEBUG -std=c99 -O2 -I$(INC_DIR)

# Directories
SRC_DIR = src
INC_DIR = src
BIN_DIR = bin

# Files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)
DEPS := $(OBJS:%.o=%.d)

# Targets
EXECUTABLE = $(BIN_DIR)/program.exe

TARGET = yacbfi

ifeq ($(OS),Windows_NT)
	TARGET := $(TARGET).exe
	BIN_DIR := $(subst /,\,$(BIN_DIR))

	REM = del /Q /F
	REMDIR = rmdir /S /Q
else
	REM = rm -rf
	REMDIR := $(REM)
endif

# Phony targets
.PHONY: all clean release

# Default target
all: $(BIN_DIR)/$(TARGET)

# Release target
release: CFLAGS = $(RELEASE_CFLAGS)
release: clean all

# Linking
$(BIN_DIR)/$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Compiling
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create bin dir
$(BIN_DIR):
	@mkdir $@


# Get git status
diff:
	$(info The status of the repository, and the volume of per-file changes:)
	@git status
	@git diff --stat

# Cleaning
clean:
	$(REMDIR) $(BIN_DIR)

# Include dependencies
-include $(DEPS)