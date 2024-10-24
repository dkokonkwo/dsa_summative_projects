# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g

# Source files
SRC = bellman_ford_algo.c build_graphs.c dijkstras_algo.c graph_functions.c heap_functions.c main.c

# Header files
HEADERS = graph.h

# Executable name
EXEC = 0-main

# Object files
OBJ = $(SRC:.c=.o)

# Default target
all: $(EXEC)

# Rule to create the executable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile source files to object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

# Phony targets
.PHONY: all clean

