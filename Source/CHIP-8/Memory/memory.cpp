#include <iostream>

using namespace std;

typedef uint8 = char; // byte type variable

int MAX_MEMORY = 4096; // max memory for slots
int STACK_MEMORY = 96; // stack memory space
int HEAP_MEMORY = MAX_MEMORY - STACK_MEMORY; // heap memory space

Memory& get_memory(){ // return new memory object
    Memory newMem = Memory(); // create temp object
    return *newMem; // returns space memory
}

private: struct Memory{ // memory structure to inherit
    using opcode = Opcode();

    // Functions
    void clear_memory(){
        
    }
    uint8* get
}

private: struct Stack{
    byte stack_memory[STACK_MEMORY]; // stack memory slots
     
    
}
private: struct Heap{
    byte heap_memory[HEAP_MEMORY]; // heap memory slots
}