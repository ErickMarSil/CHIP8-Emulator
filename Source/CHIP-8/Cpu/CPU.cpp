#include <iostream>
#include <string>
#include <cstdint>
#include <MEMORY_H.h>

struct CPU{
    uint16_t PC; // Program counter
    uint16_t IR; // Index Register
    uint8_t SP; // Stack Pointer
    uint8_t DT; // Delay timer
    uint8_t ST; // Sound timer
    uint8_t DB; // Display Buffer

    // generic registers
    uint8_t V0, V1, V2, V3, 
          V4, V5, V6, V7, 
          V8, V9, VA, VB,
          VC, VD, VE, VF;
    
    void Execute(std::string instruction){
        // execute script
    }

    void init_CPU(){ // start up cpu
        init_registers();
    }

    void init_registers(){
        // reset generic Registers 
        V0, V1, V2, V3, V4, V5, V6, V7, V8, V9, VA, VB,VC, VD, VE, VF = 0x0;

        // reset main Registers
        PC, IR, SP, DT, ST, DB = 0x0;
    }
};