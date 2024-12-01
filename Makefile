# Flags to compilation
CXX = g++
CXXFLAGS = -std=c++17 -Wall `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs`

all: main

main: cpu.o screen.o bus.o memory.o
	$(CXX) $(CXXFLAGS) ./Source/main.cpp cpu.o screen.o bus.o memory.o -o main $(LDFLAGS)

main.o:
	$(CXX) -c ./Source/main.cpp -o main.o

cpu.o:
	$(CXX) -c ./Source/cpu.cpp -o cpu.o

screen.o:
	$(CXX) -c $(CXXFLAGS) ./Source/screen.cpp -o screen.o $(LDFLAGS)

bus.o:
	$(CXX) -c ./Source/bus.cpp -o bus.o

memory.o:
	$(CXX) -c ./Source/memory.cpp -o memory.o

.PHONY: clean

clean:
	rm *.o

# # Compiler
# CXX = g++

# # Compiler and linker flags
# CXXFLAGS = -std=c++17 -Wall `sdl2-config --cflags`
# LDFLAGS = `sdl2-config --libs`

# # Target executable
# TARGET = sdl_app

# # Source file
# SRC = ./Source/screen.cpp

# # Build rule
# all: $(TARGET)

# $(TARGET): $(SRC)
# 	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

# # Clean rule
# clean:
# 	rm -f $(TARGET)