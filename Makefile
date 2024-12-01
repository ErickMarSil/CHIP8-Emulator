# Flags to compilation
CXX = g++
CXXFLAGS = -std=c++17 -Wall `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs`

all: main

main:
	$(CXX) $(CXXFLAGS) ./main.cpp -o ./main $(LDFLAGS)

# all: main

# main: cpu.o bus.o memory.o
# 	$(CXX) $(CXXFLAGS) -c ./Source/main.cpp cpu.o bus.o memory.o -o main $(LDFLAGS)

# main.o:
# 	$(CXX) ./Source/main.cpp -o main.o

# cpu.o:
# 	$(CXX) -c ./Source/cpu.cpp -o cpu.o

# bus.o:
# 	$(CXX) -c ./Source/bus.cpp -o bus.o

# memory.o:
# 	$(CXX) -c ./Source/memory.cpp -o memory.o

# .PHONY: clean

# clean:
# 	rm *.o