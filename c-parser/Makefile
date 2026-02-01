# Compiler and flags
CC = gcc
CFLAGS = -Wall

# Default target
all: cooke_parser

# Linking the final executable
cooke_parser: parser.o front.o
	$(CC) $(CFLAGS) -o cooke_parser parser.o front.o

# Compiling parser.c which depends on parser.h and front.h
parser.o: parser.c parser.h front.h
	$(CC) $(CFLAGS) -c parser.c

# Compiling front.c which depends on front.h
front.o: front.c front.h
	$(CC) $(CFLAGS) -c front.c

# Clean up build files
clean:
	rm -f *.o cooke_parser
