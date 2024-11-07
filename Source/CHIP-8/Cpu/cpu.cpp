#include <iostream>
#include <string>
#include <MEMORY_H.h>

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
    
    void Execute(string instruction){
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
struct Opcodes{
    void CALL_ADDRS(uint16& PC, uint16& SP, Memory mem, cycle& Clock){ // Set pointer counter into stack
        SP++;
        mem.add_stack(SP, PC, Clock);
        Clock--;
    }
    void SE_VX(uint16& PC, uint8 VX, uint8& KK, Memory mem, cycle& Clock){ // IF VX register and KK adds are equals
        if((VX | mem.Memory_Slots[KK]) == 0){ // checks is equal 
            PC += 2;
            Clock--;
        }
    }
    void SEN_VX(uint16& PC, uint8 VX, uint8 KK, Memory mem, cycle& Clock){ // IF VX register and KK adds are not equals
        if((VX | mem.Memory_Slots[KK]) != 0){ // checks is different
            PC += 2;
            Clock--;
        }
    }
    void SEN_VX(uint16& PC, uint8 VX, uint8 VY, cycle& Clock){ // IF VX and VY registers are not equals
        if((VX | VY) == 0){ // checks is equal
            PC += 2;
            Clock--;
        }
    }
    void LD_VX(uint16& PC, uint8* VX, uint8* addr, Memory mem, cycle& Clock){ // Loads to register VX the value in KK from memory
        VX = mem.Memory_Slots[addr];
        PC++;
        Clock--;
    }
    void ADD_VX(uint16& PC, uint8& VX, uint64 byte, Memory& mem, cycle& Clock){ // Add to VX the willed value 
        VX = VX + byte; // Add at VX to Byte
        PC++;
        Clock--;
    }

    // Others    
};