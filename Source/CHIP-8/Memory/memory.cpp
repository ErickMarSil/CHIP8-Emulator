#include <iostream>

using namespace std;

typedef char uint8; // byte type variable
typedef int cycle; // clock cycles

const int MAX_MEMORY = 4096; // max memory for slots

enum type_memmory{
    HEAP_T,
    STACK_T
};

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

    uint8 fetch_memory(uint8& address, cycle& Clock,  type_memmory& TypeM){ // access memory from address
        uint8 Content = Memory_Slots[address];
        Clock--;
        return Content;
    }
    uint8* write_memory(uint8& address, uint8 content[]){ // write content into memory
        
    }
    
};