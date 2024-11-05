#include <iostream>

using namespace std;

using byte = unsigned char; // byte type variable

int MAX_MEMORY = 4096; // max memory for slots
int ZERO_PAGE_SPACE = 512; // memory to cpu registers 
int DISPLAY_SPACE = 256; // memory to display
int CALL_STACK_SPACE = 96; // memory to cpu call stack

Memory& get_memory(){ // return new memory object
    Memory newMem = Memory(); // create temp object
    return *newMem; // returns space memory
}

private: struct Memory{ // memory structure to inherit
    // WARNING: REMOVE AFTER, SOME PROGRAMS USES OR NOT THESE SPACES, THIS APPROACH CAN INTERFER IN IT

    byte slots_memory[MAX_MEMORY - ZERO_PAGE_SPACE - DISPLAY_SPACE - CALL_STACK_SPACE]; // all memory slots removing pre-defined space memory
    byte slots_zero_page[ZERO_PAGE_SPACE]; // zero page for cpu space 
    byte slots_display[DISPLAY_SPACE]; // display space for display updates
    byte slots_call_stack[CALL_STACK_SPACE]; // call stack for stack access from cpu

    // Functions

    

}