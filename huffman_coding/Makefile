CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -pedantic

# Source files
SRC = main.c heap_functions.c huffman_functions.c create_structures.c

# Header files
HEADERS = heap.h

# Output executable
OUTPUT = 1-main

# Build target
all: $(OUTPUT)

$(OUTPUT): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) $(SRC) -o $(OUTPUT)

# Clean up the build
clean:
	rm -f $(OUTPUT)

# Rebuild the project from scratch
rebuild: clean all
