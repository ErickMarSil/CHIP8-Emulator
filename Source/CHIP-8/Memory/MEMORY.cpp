#include <iostream>
#include "MEMORY_H.h"

using namespace std;

typedef char uint8; // 8 bits type variable
typedef short uint16; // 16 bits type variable
typedef int uint32; // 32 bits type variable
typedef long uint64; // 64 bits type variable
typedef int cycle; // clock cycles

constexpr uint64 MAX_MEMORY = 4096; // max memory for slots
constexpr uint64 STACK_ADDRESS = 0xEA0; // address from stack

struct Memory{ // memory structure to inherit
    uint8 Memory::RAM[MAX_MEMORY]; // stack memory slots

    void Memory::clear_memory(){
        for (uint8 i = 0; i < MAX_MEMORY ; i++){
            RAM[i] = 0x0;
        }
    }
    void Memory::init_memory(){
        clear_memory();
    }
};