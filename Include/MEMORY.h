#include <cstdint>
#include <iostream>

class MEMORY
{
    private:
        uint8_t RAM[4096];

    public:
        MEMORY();
        ~MEMORY();

        /* Main generics functions */
        void Reset_Memory();

        /* Main functions to interact with RAM */
        uint8_t FetchRAM(uint16_t addr);
        void WriteRAM(uint16_t addr, uint16_t data);
};
