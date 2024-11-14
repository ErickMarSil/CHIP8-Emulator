#include <iostream>
#include <cstdint>
#include "MEMORY_H.h"


class MEMORY{
    void Init_Memory(){
        Reset_Memory();
    }

    void Reset_Memory(){
        for (int& i : RAM){i = 0x00;}
    }
    uint8_t FetchRAM(uint16_t& addr){
        return MEMORY::STACK[addr];
    }
    void WriteRAM(uint16_t& addr, uint16_t data, uint16_t& SP){
        MEMORY::RAM[addr] = data;
        SP++;
        return;
    }
}