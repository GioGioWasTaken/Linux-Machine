# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -O2 -Iinclude

# Linker flags
LDFLAGS =

# Source files
SRCS = src/main.c src/marks.c src/utils.c src/help.c 

# Object files
OBJS = $(SRCS:.c=.o)

# Output executable
TARGET = hermes

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS)

# Compile source files to object files
%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS)

# Phony targets
.PHONY: all clean
