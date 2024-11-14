#include <cstdint>
#include <iostream>

#ifndef MEMORY_H
#define MEMORY_H

private:
    const uint64_t MAX_BYTE = 4096;

class MEMORY {
    private:
        constexpr uint8_t RAM[MAX_BYTE];

    public:
        void Init_Memory();
        void Reset_Memory();
        uint8_t FetchRAM(uint16_t& addr);
        void WriteRAM(uint8_t& addr, uint16_t data);
}

#endif