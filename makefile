# Makefile

# Compiler
CC = g++

# Flags
CFLAGS = -Wall -Wextra -Werror

# Source names
srcMAIN_FILE = Source/main.cpp
srcMAIN_OBJECT = Source/main.o

main : #$(dpINIT_SDL_SCREEN_CPP)
	$(CC) $(srcMAIN_FILE) -o $(srcMAIN_OBJECT) $(CFLAGS)