#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "memory.hpp"
#include "bus.hpp"
#include "cpu.hpp"
#include "screen.hpp"

void insert_program(MEMORY& mem, std::string content)
{
    uint8_t addr = 0x200;

    for (uint8_t line = 0x0; line < content.size(); line++)
    {
        mem.WriteRAM(content[line], addr++);
    }
}

bool startup(std::string path)
{
    // Instaciations
    MEMORY mem;
    BUS bus(&mem);
    CPU cpu(&bus);
    SCREEN screen(&bus);

    // Read the file and send to insert torrent
    std::ifstream inFile;
    inFile.open(path);

    std::string content;
    char r;

    while(inFile >> r)
    {
        content = content + r;
    }

    // Make insertion of program in heap memory
    insert_program(mem, content);
    cpu.Execute();
}

int main(std::string args)
{
	if (startup(args) == true)
	{
		return 0;
	}
	// throw "failed in starting up the system! try again!";
}