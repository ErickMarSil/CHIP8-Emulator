# Flags to compilation
CXX = g++
CXXFLAGS = -Wall -g
LDFLAGS = -lSDL2

all: main # clean

main: main.o
	$(CXX) main.o - o main $(CXXFLAGS) $(LDFLAGS)

main.o: ./Source/main.cpp bus.o cpu.o memory.o screen.o
	$(CXX) ./Source/main.cpp -c memory.o -c bus.o -c cpu.o screen.o -o main.o

cpu.o: ./Source/cpu.cpp ./Source/cpu.hpp bus.o
	$(CXX) ./Source/cpu.cpp -c bus.o -o cpu.o

screen.o: ./Source/screen.cpp ./Source/screen.hpp bus.o
	$(CXX) ./Source/screen.cpp -c bus.o -o screen.o

bus.o: ./Source/bus.cpp ./Source/bus.hpp memory.o
	$(CXX) ./Source/bus.cpp -c memory.o -o bus.o

memory.o:
	$(CXX) ./Source/memory.cpp ./Source/memory.hpp -o memory.o

# clean:
#     rm -f $(binaries) *.o