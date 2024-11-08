#include <cstdint>
#ifndef MEMORY_H
#define MEMORY_H

constexpr uint64_t MAX_MEMORY = 1024*4;
constexpr uint8_t MAX_STACK = 16*2;

struct MEMORY {
    /*
    RAM slots begin to end 0x0 -> 0x1000 (4096 bytes)
    STACK slots begin 0xEA0 to 0xEFF (32 bytes)
    */
    uint8_t MEMORY::RAM[MAX_MEMORY];
    uint8_t MEMORY::STACK[MAX_STACK];
    /*
    CLEAR all memory slots from 0x0 to 0x1000
    */
    void MEMORY::clear_memory();
    /*
    INIT memory reseting it´s value
    */
    void MEMORY::init_memory();
};

#endif