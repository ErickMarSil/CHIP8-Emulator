#include <iostream>
#include <cstdint>
#include "MEMORY_H.h"

struct MEMORY {
    uint8_t MEMORY::RAM[MAX_MEMORY];
    uint8_t MEMORY::STACK[MAX_STACK];
    uint8_t MEMORY::FRAMEBUFFER[MAX_FRAMEBUFFER];
    uint8_t MEMORY::KEYBOARD[MAX_KEYBOARDS];
    uint8_t MEMORY::CONTROLDATA[MAX_CONTROLDATA];

    void Reset_All_Memory(){
        // Call all memorys cleaners at once
        Reset_Memory();
        Reset_Stack();
        Reset_FrameBuffer();
        Reset_KeyBoardS();
    }

    void Reset_Memory(){
        for (int& i : RAM){i = 0x00;}}
    void Reset_Stack(){
        for (int& i : STACK){i = 0x00;}}
    void Reset_FrameBuffer(){
        for (int& i : FRAMEBUFFER){i = 0x00;}}
    void Reset_KeyBoardS(){
        for (int& i : KEYBOARD){i = 0x00;}}


    uint8_t FetchRAM(uint16_t& addr){
        return MEMORY::STACK[addr];
    }
    
    uint8_t FetchHEAP(uint16_t& addr){
        return MEMORY::RAM[addr];
    }

    void WriteRAM(uint16_t& addr, uint16_t data, uint16_t& SP){
        MEMORY::RAM[addr] = data;
        SP++;
        return;
    }
};