#include <iostream>
#include <cstdint>
#include <MEMORY_H.h>

struct BUS{
    void write_stack(MEMORY& mem, uint16_t& addr, uint8_t data, uint8_t& SP){
        if (addr >= 0x0 && addr < 0x1000){
            mem.STACK[addr] = data;
            SP += 0x1;
        }
        return;
    }
    uint8_t read_stack(MEMORY& mem, uint16_t& addr) {
        if (addr >= 0x0 && addr < 0x1000){
            return mem.STACK[addr];
        }
    }
};