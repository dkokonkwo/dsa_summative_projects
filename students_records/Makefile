CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -pedantic

# Source files
SRC = main.c rbtrees_functions.c

# Header files
HEADERS = rbtrees.h

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
