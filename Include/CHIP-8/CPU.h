#include <cstdint>
#include <string>

#ifndef CPU_H
#define CPU_H

public:
    struct CPU{

        uint8_t VRegs[16]; /* Register V0 to VF */
        uint16_t IR; /* Register "Index Register" */
        uint8_t SP; /* Register "Stack Pointer" */
        uint8_t DT; /* Register "Delay Timer" */
        uint8_t ST; /* Register "Sounder Timer" */
        uint8_t PC; /* Register "Pointer Counter" */

        /*OPCODES DECLARATION*/
        uint16_t SYS();  uint16_t CLS(); uint16_t RET();  uint16_t JP(); 
        uint16_t CALL(); uint16_t SE();  uint16_t SEN();  uint16_t LD();
        uint16_t ADD();  uint16_t OR();  uint16_t AND();  uint16_t XOR(); 
        uint16_t SUB();  uint16_t SHR(); uint16_t SUBN(); uint16_t SHL();
        uint16_t SNE();

        // Read Byte(index) instruction from PC location
        // Use the Byte(index) to get instruction and nums of Cycles
        // Read rest of bytes that i need
        // Execute the instruction

    };

#endif