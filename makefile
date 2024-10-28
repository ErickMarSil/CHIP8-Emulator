# Makefile

# Compiler
CC = g++

# Targets names
tgMain = all

# Sources
srcMain = src/main.cpp
srcMainDest = src/main

all: 
	$(CC) $(srcMain) -o $(srcMainDest)
