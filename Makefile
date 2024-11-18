# Flags to compilation
CXX = g++
CXXFLAGS = -Wall -g
LDFLAGS = -lSDL2

# Targets Sources
all: main
memoryT:Source/CHIP-8/MEMORY.cpp
busT:Source/CHIP-8/BUS.cpp
cpuT:Source/CHIP-8/CPU.cpp

# Targets Compilation
mem:
    $(CXX) $(CXXFLAGS) memoryT -o Source/CHIP-8/MEMORY.o $(LDFLAGS)

bus:
    $(CXX) $(CXXFLAGS) busT -o Source/CHIP-8/BUS.o $(LDFLAGS)

cpu:
    $(CXX) $(CXXFLAGS) cpuT	-o Source/CHIP-8/CPU.o $(LDFLAGS)

main: mem, bus, cpu
    $(CXX) $(CXXFLAGS) main.cpp -o main $(LDFLAGS)

# Clean main
clean:
    rm -f main