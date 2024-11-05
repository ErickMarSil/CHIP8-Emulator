#include <iostream>
#include <cstdiny>

using namespace std;

typedef uint8 = byte; // byte type variable
typedef uint16[16]; // 16 bytes type
typedef uint16[32]; // 32 bytes type

int MAX_MEMORY = 4096; // max memory for slots
int STACK_MEMORY = 64; // stack memory
int ZERO_PAGE_SPACE = 512; // memory to cpu registers 
int DISPLAY_SPACE = 256; // memory to display
int CALL_STACK_SPACE = 96; // memory to cpu call stack

Memory& get_memory(){ // return new memory object
    Memory newMem = Memory(); // create temp object
    return *newMem; // returns space memory
}

private: struct Memory{ // memory structure to inherit
    // WARNING: REMOVE AFTER, SOME PROGRAMS USES OR NOT THESE SPACES, THIS APPROACH CAN INTERFER IN IT

    byte slots_memory[MAX_MEMORY - STACK_MEMORY - ZERO_PAGE_SPACE - DISPLAY_SPACE - CALL_STACK_SPACE]; // all memory slots removing pre-defined space memory
    byte slots_zero_page[ZERO_PAGE_SPACE]; // zero page for cpu space 
    byte slots_display[DISPLAY_SPACE]; // display space for display updates
    byte slots_call_stack[CALL_STACK_SPACE]; // call stack for stack access from cpu
    byte 

    using opcode = Opcode();

    // Functions
    void clear_memory(){
        for (int m, z, d, c, s; (m + z + d + c + s) < MAX_MEMORY; m++){ // clear all memorys slots in all lists
            slots_memory[m] = 0x0;
            slots_zero_page[z++] = 0x0;
            slots_display[d++] = 0x0;
            slots_call_stack[c++] = 0x0;   
        }
    }

}

private : struct Opcode{
    byte RET(Memory* mem, u_16* SP){
        return;
    }
}