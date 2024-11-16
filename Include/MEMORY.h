#include <cstdint>
#include <iostream>

class MEMORY
{
    private:
        uint8_t RAM[4096];

    public:
        MEMORY();
        ~MEMORY();

        // Main generics functions
        void Reset_Memory();

        // Main functions to interact with RAM
        uint8_t FetchRAM(uint8_t addr);
        void WriteRAM(uint8_t addr, uint8_t data);

        // Sub function to fetch instruction 
        // uint32_t FetchHEAP(uint16_t addr);
};
