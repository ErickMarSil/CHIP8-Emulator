#include <iostream>
#include <cstdint>
#include "MEMORY.h"


MEMORY::MEMORY(){
    Reset_Memory();
}
void MEMORY::Reset_Memory(){
    for (int i : MEMORY::RAM){i = 0x00;}
}

uint8_t MEMORY::FetchRAM(uint16_t addr){
    if (addr <= 0x1000 && addr >= 0x0){
        return MEMORY::RAM[addr];
    }
    return (uint8_t)0x00;
}
void MEMORY::WriteRAM(uint16_t addr, uint16_t data){
    if (addr <= 0x1000 && addr >= 0x0){
        MEMORY::RAM[addr] = data;
    }
    return;
}