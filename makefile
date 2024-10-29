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

all: 
	$(CC) $(srcMain) -o $(srcMainDest) $(CFLAGS)
