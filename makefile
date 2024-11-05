# Variáveis
CXX = g++
CXXFLAGS = -Wall -g
LDFLAGS = -lSDL2

# Alvo de build
all: main

main: Source/main.cpp
	$(CXX) $(CXXFLAGS) Source/main.cpp -o Source/main $(LDFLAGS)

# Limpeza
clean:
	rm -f main