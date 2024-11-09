# Variáveis
CXX = g++
CXXFLAGS = -Wall -g
LDFLAGS = -lSDL2

# Alvo de build
all: main

main: main.cpp
    $(CXX) $(CXXFLAGS) main.cpp -o main $(LDFLAGS)

# Limpeza
clean:
    rm -f main