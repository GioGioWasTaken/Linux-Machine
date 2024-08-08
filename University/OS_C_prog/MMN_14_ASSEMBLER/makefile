# Compiler and flags
CC = gcc
CFLAGS = -IHeaders -Wall -Wextra -ansi -pedantic -g 
# Directories
SRC_DIR = SRC
OBJ_DIR = OBJ

# Sources and objects
SOURCES = Assembler.c $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:.c=.o)

# Output executable
TARGET = AwesomeAssembler

# Default rule
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

# Rule to build object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build object files from SRC directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean build artifacts
clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all clean
