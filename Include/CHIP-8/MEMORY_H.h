#ifndef MEMORY_H
#define MEMORY_H

constexpr uint64_t MAX_MEMORY = 4096;

struct MEMORY {
    /*
    RAM slots begin to end 0x0 -> 0x1000 (4096 bytes)
    */
    uint8_t RAM[MAX_MEMORY];
    /*
    CLEAR all memory slots from 0x0 to 0x1000
    */
    void clear_memory();
    /*
    INIT memory reseting it´s value
    */
    void init_memory();
};

#endif