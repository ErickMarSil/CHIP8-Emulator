# Makefile

# Compiler
CC = g++

# Flags
CFLAGS = -Wall -Wextra -Werror

# Targets names
tgMain = all

# Sources
srcMain = src/main.cpp
srcMainDest = src/main
srcScreenSetUp = src/sreen_SDL_setup/init_SDL_screen.cpp

all: 
	$(CC) $(srcMain) -o $(srcMainDest) $(CFLAGS)
