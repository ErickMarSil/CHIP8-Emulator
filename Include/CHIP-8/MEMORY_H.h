#include <cstdint>
#include <iostream>

#ifndef MEMORY_H
#define MEMORY_H

private:
    constexpr uint64_t MAX_MEMORY = 1024*4;
    constexpr uint64_t MAX_FRAMEBUFFER = 1024;
    constexpr uint8_t  MAX_STACK = 16*2;
    constexpr uint8_t  MAX_KEYBOARDS = 16*2;
    constexpr uint8_t  MAX_CONTROLDATA = 16*2;

public:
    struct MEMORY {
        /*
        RAM slots begin to end 0x0 -> 0x1000 (4096 bytes)
        STACK slots begin 0xEA0 to 0xEFF (32 bytes)
        */
        uint8_t RAM[MAX_MEMORY]; /*RAM or HEAP memory to program it self*/
        uint8_t STACK[MAX_STACK]; /*STACK or WRITE memory to cpu process and fast access*/
        uint8_t FRAMEBUFFER[MAX_FRAMEBUFFER]; /*FRAMEBUFFER or DISPLAY to storage pixels*/
        uint8_t KEYBOARD[MAX_KEYBOARDS]; /*KEYBOARD STATUS or INPUT handle the user inputs*/
        uint8_t CONTROLDATA[MAX_CONTROLDATA]; /*CO*/
        /*
        Clear all memorys types such as RAM, STACK, FRAMEBUFFER
        */
        void Reset_All_Memory();

        /*Reset the Ram/Heap memory setting 0x00 bytes on it*/
        void Reset_Memory();
        /*Reset the Stack memory setting 0x00 bytes on it*/
        void Reset_Stack();
        /*Reset the Framebuffer bucket setting 0x00 bytes on it*/
        void Reset_FrameBuffer();
        /*Reset the Keyboard inputs setting 0x00 bytes on it*/
        void Reset_KeyBoardS();

        /* Can fetch byte from heap or ram slots:
            * RAM
            * HEAP*/
        uint8_t FetchRAM(uint16_t& addr);
        uint8_t FetchHEAP(uint16_t& addr);

        /* Write into RAM or STACK memory*/
        void WriteRAM(uint16_t& addr, uint16_t data);
    };

#endif