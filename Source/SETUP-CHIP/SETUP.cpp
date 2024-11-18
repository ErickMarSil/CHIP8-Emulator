#include <iostream>
#include <string>

#include "MEMORY.h"
#include "BUS.h"
#include "CPU.h"

bool startup()
{
    // Make insertion of program in heap memory
    MEMORY mem;
    insert_program(mem);

    // Set Instance of bus parsing the memory object
    BUS bus;
    bus.SetMemory(mem);

    // Create new instance of CPU and set the bus
    CPU cpu;
    cpu.SetBus(bus);

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