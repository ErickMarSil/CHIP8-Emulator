#include <iostream>
#include <string>
#include <cstdint>
#include <MEMORY_H.h>

struct CPU{
    uint64_t DB; // Display Buffer
    uint16_t IR; // Index Register
    uint16_t PC; // Program counter
    uint8_t SP;  // Stack Pointer
    uint8_t TR;  // Timer Register
    uint8_t ST;  // Sound timer

    // generic registers
    uint8_t V0, V1, V2, V3, 
        V4, V5, V6, V7, 
        V8, V9, VA, VB,
        VC, VD, VE, VF;
    
    void init_CPU(){
        init_registers();
    }

    void init_registers(){
        // reset generic Registers 
        V0, V1, V2, V3, V4, V5, V6, V7, V8, V9, VA, VB,VC, VD, VE, VF = 0x0;

        // reset main Registers
        PC, IR, SP, ST, DB = 0x0;
    }
};