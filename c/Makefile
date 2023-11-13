# Compiler settings
CC = gcc
CFLAGS = -Wall -Isrc
LDFLAGS =

# Directories
SRC_DIR = src
TESTS_DIR = src/tests
OBJ_DIR = obj
BIN_DIR = bin

# Find all source and test files
SRCS = $(wildcard $(SRC_DIR)/*.c)
TESTS = $(wildcard $(TESTS_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TEST_BINS = $(TESTS:$(TESTS_DIR)/%.c=$(BIN_DIR)/%)

# Default target
all: $(TEST_BINS)

# Test binaries depend on object files
$(BIN_DIR)/%: $(TESTS_DIR)/%.c $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $< $(OBJS) -o $@ $(LDFLAGS)

# Object file rules
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all clean
