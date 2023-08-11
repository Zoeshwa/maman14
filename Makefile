# Compiler options
CC := gcc
CFLAGS := -Wall -ansi -pedantic
LDFLAGS :=

# Directories
SRC_DIR := src
INC_DIR := include
OBJ_DIR := obj
BIN_DIR := bin

# Files
EXECUTABLE := assembler
SOURCES := $(wildcard $(SRC_DIR)/*.c)
HEADERS := $(wildcard $(INC_DIR)/*.h)
OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

# Default target
all: directories $(EXECUTABLE)

# Create necessary directories
directories:
	$(shell if not exist $(OBJ_DIR) mkdir $(OBJ_DIR))
	$(shell if not exist $(BIN_DIR) mkdir $(BIN_DIR))



# Link object files and create the executable
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $(BIN_DIR)/$(EXECUTABLE) $^

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c -o $@ $<

# Clean intermediate object files and the executable
clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(BIN_DIR)

# Clean and rebuild the project
rebuild: clean all

# Phony targets (do not correspond to actual files)
.PHONY: all directories clean rebuild
