#include <iostream>

using namespace std;

typedef char uint8 = undefined char; // byte type variable

const int MAX_MEMORY = 4096; // max memory for slots
const int STACK_MEMORY = 96; // stack memory space
const int HEAP_MEMORY = MAX_MEMORY - STACK_MEMORY; // heap memory space

struct Memory{ // memory structure to inherit
    // using opcode = Opcode();

    // Functions
    void clear_memory(){
        // clear memory (heap and stack)
    }
    uint8* read_memory(uint8& address){
        // access memory from address
    }
    uint8* write_memory(uint8& address, uint8 content[]){
        // write content into memory
    }
    
};

struct Stack{
    uint8 stack_memory[MAX_MEMORY]; // stack memory slots
    void clear_stack(){
        for (uint8 i = 0; i < stack_memory.size() ; i++){

        }
    }
};
struct Heap{
    uint8 heap_memory[HEAP_MEMORY]; // heap memory slots
};