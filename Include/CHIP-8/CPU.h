#include <cstdint>
#include <string>

#ifndef CPU_H
#define CPU_H

public:
    enum OPCODES:
        CALL, /* Calls subroutine at nnn address */
        SEB,  /* Checks if Register is equal to Byte(addr) */ 
        SEN,  /* Checks if Register is NOT equal to Byte(addr) */ 
        SER,  /* Checks if Register X is equal to register Y */ 
        LD,   /* Loads into Register X the value in kk */ 
        ADD,  /* Add the value Register Y with kk into X */

public:
    struct CPU{

        uint8_t VRegs[16]; /* Register V0 to VF */
        uint16_t IR; /* Register "Index Register" */
        uint8_t SP; /* Register "Stack Pointer" */
        uint8_t DT; /* Register "Delay Timer" */
        uint8_t ST; /* Register "Sounder Timer" */
        uint8_t PC; /* Register "Pointer Counter" */

        // Read Byte(index) instruction from PC location
        // Use the Byte(index) to get instruction and nums of Cycles
        // Read rest of bytes that i need
        // Execute the instruction
        
    };

#endif