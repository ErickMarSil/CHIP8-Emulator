#include <iostream>
#include <Include/CHIP-8/MEMORY_H.hpp>

using namespace std;

typedef char uint8; // 8 bits type variable
typedef short uint16; // 16 bits type variable
typedef int uint32; // 32 bits type variable
typedef long uint64; // 64 bits type variable
typedef int cycle; // clock cycles

constexpr uint64 MAX_MEMORY = 4096; // max memory for slots
constexpr uint64 STACK_ADDRESS = 0xEA0; // address from stack

struct Memory{ // memory structure to inherit
    // using opcode = Opcode();
    // creates object
    uint8 Memory_Slots[MAX_MEMORY]; // stack memory slots

    // FUNCTIONS
    void clear_memory(){ // clear memory
        for (uint8 i = 0; i < MAX_MEMORY ; i++){
            Memory_Slots[i] = 0x0; // reset the stack
        }
    }
    void init_memory(){ // initialize memory
        // initialize memory
        clear_memory();
    }
    void add_stack(uint8& addr, uint32& data, cycle& Cycles){
        Memory_Slots[addr] = data; // set data into stack
        Cycles--; // remove cycle
    }
    
};