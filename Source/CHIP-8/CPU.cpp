#include <iostream>
#include "CPU.h"
#include "BUS.h"

CPU::CPU()
{
    BUS bus;

    PC = nullptr;
    SP = &bus.addressLimits[2][0];
}

bool CPU::Execute()
{
    
}

/* OPCODE FUNCTION DECLARED (ALU)*/

uint16_t CPU::SYS (uint16_t addr){}
uint16_t CPU::CLS()
{
    // Clear screen with SDL function
    for (uint8_t i; i < 0x160; i += 0x1)
    {
        bus.Write_Mem(i, );
    }
    // Call SDL writer
}
uint16_t CPU::RET()
{
    // Set Pointer counter to top of the stack
    PC = &bus.addressLimits[2][0];
    // Subtract one to Stack pointer
    SP -= 0x1;
    return 0x0;
}
uint16_t CPU::JP(uint16_t& addr)
{
    // Jumps to cetain address in memory
    PC = (uint16_t*)addr;
    return 0x0;
}
uint16_t CPU::CALL(uint16_t addr)
{
    // Jumps to cetain label
    PC = (uint16_t*)addr;
    return 0x0;
}
uint16_t CPU::SE(uint8_t VX, uint8_t byte)
{
    // Checks if VX is equal to kk(byte)
    if((VX - byte) == 0x0)
    {
        PC += 2;
        return 0x0;
    }
    PC++;
}
uint16_t CPU::SNE(uint8_t VX, uint8_t byte)
{
    // Checks if VX is not equal to kk(byte)
    if((VX - byte) != 0x0)
    {
        PC += 2;
        return 0x0;
    }
    PC++;
}
uint16_t CPU::SE(uint8_t VX, uint8_t VY)
{
    // Checks if VX is equal to VY
    if((VX - VY) == 0x0)
    {
        PC += 2;
    }
    return 0x0;
}
uint16_t CPU::LD(uint8_t& VX, uint8_t byte)
{
    // Set register VX to value in kk(byte)
    VX = byte;
    PC++;
    return 0x0;
}
uint16_t CPU::ADD(uint8_t& VX, uint8_t byte)
{
    // Set VX register to value of it self with kk(byte)
    VX += byte;
    PC++;
    return 0x0;
}
uint16_t CPU::LD(uint8_t& VX, uint8_t VY)
{
    // Set value of 
    VX = VY;
    PC++;
    return 0x0;
}
// Bitwise operation
uint16_t CPU::OR(uint8_t& VX, uint8_t& VY)
{
    VX = VX | VY;
    PC++;
    return 0x0;
}
uint16_t CPU::AND (uint8_t& VX, uint8_t& VY)
{
    VX = VX & VY;
    PC++;
    return 0x0;
}
uint16_t CPU::XOR (uint8_t& VX, uint8_t& VY)
{
    VX = VX ^ VY;
    PC++;
    return 0x0;
}
uint16_t CPU::ADD (uint8_t& VX, uint8_t VY)
{
    // Add into VX the it self with VY and add carry
    if (VX + VY > 0x255 || VX + VY < 0x0)
    {
        VRegs[15] = 0x1;
        VX += VY;
    }
    PC++;
    return 0x0;
}
uint16_t CPU::SUB (uint8_t& VX, uint8_t VY)
{
    // Sub into VX the it self with VY and add carry
    VX -= VY;
    VRegs[15] = VX > VY ? 0x1 : 0x0;
    PC++;
    return 0x0;
}
uint16_t CPU::SHR (uint8_t& VX)
{
    // Check if last bit in register is equal to 1
    if ((~(VX) & 0x00000001) == 0x0)
    {
        VRegs[15] = 0x1;
    }
    PC++;
    return 0x0;
}
uint16_t CPU::SUBN(uint8_t& VX, uint8_t VY)
{
    // Sub into VX the it self, if VX > VY VF = 0x1
    VX -= VY;
    VRegs[15] = VX < VY ? 0x1 : 0x0;
    PC++;
    return 0x0;
}
uint16_t CPU::SHL (uint8_t& VX)
{
    // Check if last bit in register is equal to 1
    if ((~(VX) & 0x10000000) == 0x0)
    {
        VRegs[15] = 0x1;
    }
    PC++;
    return 0x0;
}
uint16_t CPU::SNE (uint8_t VX, uint8_t VY)
{
    // Checks if the VX is different of VY
    if ((VX - VY) != 0x0)
    {
        PC += 2;
        return 0x0;
    }
    PC++;
}