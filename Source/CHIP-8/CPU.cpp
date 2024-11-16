#include <iostream>
#include <vector>
#include "CPU.h"
#include "BUS.h"

CPU::CPU()
{
    BUS bus;

    PC = 0x0;
    SP = 0x160;

    CPU::OPTable = {
        &CPU::SYS, &CPU::CLS, &CPU::RET,
        &CPU::JP,  &CPU::CALL,&CPU::SE,
        &CPU::SNE, &CPU::SE,  &CPU::LD,
        &CPU::ADD, &CPU::LD,  &CPU::OR,
        &CPU::AND, &CPU::XOR, &CPU::ADD,
        &CPU::SUB, &CPU::SHR, &CPU::SUBN,
        &CPU::SHL, &CPU::SNE
    };

}

bool CPU::Execute(uint8_t& Clock)
{
    uint8_t func = 0x0;

    while (Clock != 0)
    {
        // Must Fetch function
        func = bus.Fetch_Mem(PC, DevicesConn::Stack);

        // Must Fetch data
        // Reduce 1 into clock
        // Read next
    }
    return Clock == 0;
}


/* OPCODE FUNCTION DECLARED (ALU)*/
uint16_t CPU::Op0(uint32_t& bytes)
{
    uint8_t op = 0x0;

    // Calc op

    switch (op)
    {
    case 0x0E0: // (CLS) Clear screen in frame buffer
        for (uint8_t i; i < 0x160; i += 0x1)
        {
            uint8_t a = 0x0;
            bus.Write_Mem(i, DevicesConn::Stack, 0x00, SP);
        }
        break;
    case 0x0EE: // (RET) Retunr to caller point
        PC = 0x0;
        SP -= 0x1;
        return 0x0;
        break;
    default:
        break;
    }
}
uint16_t CPU::Op1(uint32_t& bytes) // (JP) Jumps to cetain address in memory
{
    uint16_t addr;

    PC = addr;
    return 0x0;
}
uint16_t CPU::Op2(uint32_t& byte) // (CALL) Call a cetain label
{
    uint16_t addr;

    PC = addr;
    return 0x0;
}

uint16_t CPU::Op3(uint32_t& byte) // (SE) If VX is equal to kk(byte)
{
    uint8_t VX;
    uint8_t byteVal;

    if((VX - byteVal) == 0x0)
    {
        PC += 2;
        return 0x0;
    }
    PC++;
}

uint16_t CPU::Op4(uint32_t& byte) // (SNE) If not VX equal to kk(byte)
{
    uint8_t VX;
    uint8_t byteVal;

    if((VX - byteVal) != 0x0)
    {
        PC += 2;
        return 0x0;
    }
    PC++;
}
uint16_t CPU::Op5(uint32_t& byte){
    // (SE) If VX is equal to VY
    uint8_t VX;
    uint8_t VY;

    if((VX - VY) == 0x0)
    {
        PC += 2;
    }
    return 0x0;
}
uint16_t CPU::Op6(uint32_t& byte){
    // (LD) Load into register VX the value kk(byte)
    uint8_t VX;
    uint8_t byteVal;

    VX = byteVal;
    PC++;
    return 0x0;
}
uint16_t CPU::Op7(uint32_t& byte){
    // (ADD) Add VX register to it self and with kk(byte)
    uint8_t VX;
    uint8_t byteVal;

    VX += byteVal;
    PC++;
    return 0x0;
}
uint16_t CPU::Op8(uint32_t& byte){
    uint8_t op = 0x0;
    uint8_t VX = 0x0;
    uint8_t VY = 0x0;
    uint8_t byteVal;

    // Calc op

    switch (op)
    {
    case 0x0: // (LD) Load into VX value in VX
        VX = VY;
        PC++;
        return 0x0;
        break;
    case 0x1: // (OR) Bitwise operation (0, 1) -> 1
        VX = VX | VY;
        PC++;
        return 0x0;
        break;
    case 0x2: // (AND) Bitwise operation (0, 1) -> 0
        VX = VX & VY;
        PC++;
        return 0x0;
        break;
    case 0x3: // (XOR) Bitwise operation (1, 1) -> 0
        VX = VX ^ VY;
        PC++;
        return 0x0;
        break;
    case 0x4: // (ADD) Add VX with it self with VY using Carry
        if (VX + VY > 0x255 || VX + VY < 0x0)
        {
            VRegs[15] = 0x1;
            VX += VY;
        }
        PC++;
        return 0x0;
        break;
    case 0x5: // (SUB) Add VX with it self with VY using Carry
        VX -= VY;
        VRegs[15] = VX > VY ? 0x1 : 0x0;
        PC++;
        return 0x0;
        break;
    case 0x6: // (SHR) Check least significant bit in VX, if so VF = 1
        if ((~(VX) & 0x00000001) == 0x0)
        {
            VRegs[15] = 0x1;
        }
        PC++;
        return 0x0;
        break;
    case 0x7: // (SUBN) Sub VX with VY, if VX ¿ VY then VF = 1
        VX -= VY;
        VRegs[15] = VX < VY ? 0x1 : 0x0;
        PC++;
        return 0x0;
        break;
    case 0xE: // (SHR) Check most significant bit in VX, if so VF = 1
        if ((~(VX) & 0x10000000) == 0x0)
        {
            VRegs[15] = 0x1;
        }
        PC++;
        return 0x0;
        break;
    default: // (XXX) Non exist function treatment
        break;
    }
}
uint16_t CPU::Op9(uint32_t& byte){
    // (SNE) If not, VX is different of VY
    uint8_t VX;
    uint8_t VY;

    if ((VX - VY) != 0x0)
    {
        PC += 2;
        return 0x0;
    }
    PC++;
}
