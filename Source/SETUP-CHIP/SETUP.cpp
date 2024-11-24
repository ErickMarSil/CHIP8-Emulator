#include <iostream>
#include <string>

#include "MEMORY.h"
#include "BUS.h"
#include "CPU.h"
#include "SCREEN.h"

bool startup()
{

    // Instaciations
    CPU cpu;
    BUS bus;
    MEMORY mem;
    SCREEN screen;

    // Make insertion of program in heap memory
    insert_program(mem);

    cpu.Execute();
}

void insert_program(MEMORY& mem)
{
    std::string content;
    uint8_t addr = 0x200; 

    for (uint8_t line = 0x0; line < content.size(); line++)
    {
        mem.WriteRAM(content[line], addr++);
    }
}