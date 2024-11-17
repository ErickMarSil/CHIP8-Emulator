#include <iostream>
#include <cstdint>
#include "MEMORY.h"


MEMORY::MEMORY()
{
    Reset_Memory();
}
void MEMORY::Reset_Memory()
{
    for (int i : MEMORY::RAM){MEMORY::RAM[i] = 0x00;}
}

uint8_t MEMORY::FetchRAM(uint8_t addr)
{
    if (addr <= 0x1000 && addr >= 0x0) // Check if overload the memory
    {
        return MEMORY::RAM[addr];
    }
    return (uint8_t)0x00;
}
void MEMORY::WriteRAM(uint8_t addr, uint8_t data)
{
    if (addr <= 0x1000 && addr >= 0x0)
    {
        MEMORY::RAM[addr] = data;
    }
    return;
}