#include <iostream>
#include <Include/CHIP-8/MEMORY_H.hpp>

using namespace std;

typedef char uint8; // 8 bits type variable
typedef short uint16; // 16 bits type variable
typedef int uint32; // 32 bits type variable
typedef long uint64; // 64 bits type variable
typedef int cycle; // clock cycles

struct CPU{
    Registers* registers;
    
};
struct Registers{
    uint16 PC; // Program counter
    uint16 IR; // Index Register
    uint8 SP; // Stack Pointer
    uint8 DT; // Delay timer
    uint8 ST; // Sound timer
    uint8 DB; // Display Buffer

    Opcodes opcode; // opcode table actions

    // generic registers
    uint8 V0, V1, V2, V3, 
          V4, V5, V6, V7, 
          V8, V9, VA, VB,
          VC, VD, VE, VF;
    
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
struct Opcodes{
    void CALL_ADDRS(uint16& PC, uint8& SP, Memory& mem, cycle& Clock){ // Set pointer counter into stack
        SP++;
        mem.add_stack(SP, PC, Clock);
        Clock--;
    }
    void SE_VX(uint16& PC, uint8& VX, uint8& KK, Memory& mem, cycle& Clock){ // IF VX register and KK adds are equals
        if((VX | mem[KK]) == 0){
            PC += 2;
            Clock--;
        }
    }
    void SEN_VX(uint16& PC, uint8& VX, uint8& KK, Memory& mem, cycle& Clock){ // IF VX register and KK adds are not equals
        if((VX | mem[KK]) != 0){
            PC += 2;
            Clock--;
        }
    }
    void SEN_VX(uint16& PC, uint8& VX, uint8& VY, cycle& Clock){ // IF VX and VY registers are not equals
        if((VX | VY) != 0){
            PC += 2;
            Clock--;
        }
    }
    void LD_VX(uint16& PC, ){ // Loads to register VX the value in KK from memory

    }
};