# Makefile

# Compiler
CC = g++

# Flags
CFLAGS = -Wall -Wextra -Werror

# Targets names
tgMAIN = main.o

# Source names
srcMAIN_FILE = Source/main.cpp
srcMAIN_OBJECT = Source/main.o

# Dependencies names 
dpINIT_SDL_SCREEN_CPP = Source/Src/init_SDL_screen.cpp

$(tgMAIN) : $(dpINIT_SDL_SCREEN_CPP)
	$(CC) $(srcMAIN_FILE) -o $(srcMAIN_OBJECT) $(CFLAGS)