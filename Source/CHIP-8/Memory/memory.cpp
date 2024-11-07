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
    void add_stack(uint16& SP, uint16& data, cycle& Cycles){
        if (SP > (MAX_MEMORY)&& SP < (MAX_MEMORY - STACK_ADDRESS)){
            return;
        }
        Memory_Slots[SP] = data; // set data into stack
        Cycles--; // remove cycle
    }
    void pop_byte(){

    }
    void push_byte(){

    }
};