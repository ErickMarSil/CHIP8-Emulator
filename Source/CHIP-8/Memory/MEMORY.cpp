#include <iostream>
#include <cstdint>
#include "MEMORY_H.h"

constexpr uint64_t MAX_MEMORY = 1024*4; // max memory for slots
constexpr uint8_t MAX_STACK = 16*2; // address from stack

struct MEMORY{ // memory structure to inherit
    uint8_t MEMORY::RAM[MAX_MEMORY];
    uint8_t MEMORY::STACK[MAX_STACK];

    void MEMORY::clear_memory(){
        for (uint8_t& slot : MEMORY::RAM){
            slot = 0x0;
        }
    }
    void MEMORY::init_memory(){
        clear_memory();
    }
};