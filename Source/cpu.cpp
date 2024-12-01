#include <iostream>
#include <random>
#include <vector>
#include <stdio.h>

#include "cpu.hpp"
#include "bus.hpp"

CPU::CPU(BUS* busRef)
{
    Reset();
    bus = busRef;
    // CPU::OPTable =
    // {
    //     CPU::Op0, CPU::Op1, CPU::Op2, CPU::Op3,
    //     CPU::Op4, CPU::Op5, CPU::Op6, CPU::Op7,
    //     CPU::Op8, CPU::Op9, CPU::OpA, CPU::OpB,
    //     CPU::OpC, CPU::OpD, CPU::OpE, CPU::OpF
    // };

}

void CPU::Reset()
{
    // Set program counter in top of the heap in 0x200
    // Set stack pointer in top of the stack 0x 0x160
    PC = 0x200;
    SP = 0x16;
    FunctI = 0x0;
    for (uint8_t& i : ParamsV){i = 0x0;}

    I, PC = 0x00;
    SP, DT, ST = 0x0;

    for (uint8_t& i : VRegs){i = 0x0;}

    ListOld = {0x1};
}

bool CPU::Execute()
{
    // Fetch functions and set bytes paramters
    Fetch();

    // TEMPORARILY ----
    if( /* FunctI <= (sizeof(OPTable) / 4) */ FunctI <= 0xF)
    {
        // Request a clock (Non used yet)
        RequestClock();

        // Call function in opcode
        switch (FunctI)
        {
        case 0x0: Op0();
            break;
        case 0x1: Op1();
            break;
        case 0x2: Op2();
            break;
        case 0x3: Op3();
            break;
        case 0x4: Op4();
            break;
        case 0x5: Op5();
            break;
        case 0x6: Op6();
            break;
        case 0x7: Op7();
            break;
        case 0x8: Op8();
            break;
        case 0x9: Op9();
            break;
        case 0xA: OpA();
            break;
        case 0xB: OpB();
            break;
        case 0xC: OpC();
            break;
        case 0xD: OpD();
            break;
        case 0xE: OpE();
            break;
        case 0xF: OpF();
            break;
        default:
            break;
        }

        // Reduce Clock (Non used yet)
        ReduceClock(3);

        SP++;
        return true;
    }
    else
    {
        // raises an error and return
        return false;
    }
}

// Fetch 2 bytes from memory =========================================

uint16_t CPU::Fetch()
{
    uint8_t entire[2] = 
    {
        bus->Fetch_Mem((PC >> 8) & 0xFF, DevicesConn::Heap),
        bus->Fetch_Mem((PC << 8) & 0xFF, DevicesConn::Heap)
    };
    FunctI = (entire[0] >> 4) & 0b0000;

    ParamsV[0] = (entire[0] << 4);
    ParamsV[1] = (entire[1] >> 4);
    ParamsV[2] = (entire[1] << 4);

    return 0x0;
}

// Request a CPU clock to the function ==============================
uint8_t CPU::RequestClock()
{
    if (Clock == 0)
    {
        Clock += 3;
    }
    return 0x0;
}
uint8_t CPU::ReduceClock(uint8_t amountClock)
{
    if (Clock + 3 >= 3)
    {
        Clock -= 3;
    }
    return 0x0;
}


// OPCODE FUNCTION DECLARED (ALU) ===================================
uint16_t CPU::Op0()
{
    uint8_t op = (FunctI >> 4) & 0b0000;

    switch (op)
    {
    case 0x0E0: // (CLS) Clear screen in frame buffer
        for (uint8_t inc; inc < 0x160; inc += 0x1)
        {
            uint8_t addr = inc + 0x128;
            bus->Write_Mem(addr, DevicesConn::FrameBuffer, 0x00);
        }
        break;
    case 0x0EE: // (RET) Retunr to caller point
        PC = 0x200;
        SP -= 0x1;
        break;
    default:
        break;
    }
    return 0x0;
}

uint16_t CPU::Op1() // (JP) Jumps to cetain address in memory ======
{
    uint16_t addr = ParamsV[0] | ParamsV[1] | ParamsV[2];

    PC = addr;
    return 0x0;
}
uint16_t CPU::Op2() // (CALL) Call a cetain label ==================
{
    uint16_t addr = ParamsV[0] | ParamsV[1] | ParamsV[2];

    PC = addr;
    return 0x0;
}

uint16_t CPU::Op3() // (SE) If VX is equal to kk(byte) ============
{
    uint8_t VX = ParamsV[0];
    uint8_t byteVal = ParamsV[1] | ParamsV[2];

    if((VX - byteVal) == 0x0)
    {
        PC+=2;
    };
    return 0x0;
}

uint16_t CPU::Op4() // (SNE) If not VX equal to kk(byte) =========
{
    uint8_t VX = ParamsV[0];
    uint8_t byteVal = ParamsV[1] | ParamsV[2];

    if((VX - byteVal) != 0x0)
    {
        PC+=2;
        return 0x0;
    }
    PC+=2;
    return 0x0;
}
uint16_t CPU::Op5()
{
    // (SE) If VX is equal to VY
    uint8_t VX = ParamsV[1];
    uint8_t VY = ParamsV[2];

    if((VRegs[VX] - VRegs[VY]) == 0x0)
    {
        PC+=2;
    }
    return 0x0;
}
uint16_t CPU::Op6()
{
    // (LD) Load into register VX the value kk(byte) ============
    uint8_t VX = ParamsV[0];
    uint8_t byteVal = ParamsV[1] | ParamsV[2];

    VRegs[VX] = byteVal;
    return 0x0;
}
uint16_t CPU::Op7()
{
    // (ADD) Add VX register to it self and with kk(byte) =======
    uint8_t VX = ParamsV[0];
    uint8_t byteVal = ParamsV[1] | ParamsV[2];

    VRegs[VX] += byteVal;
    return 0x0;
}
uint16_t CPU::Op8()
{
    uint8_t op = ParamsV[2];
    uint8_t VX = ParamsV[0];
    uint8_t VY = ParamsV[1];
    uint8_t byteVal = ParamsV[1] | ParamsV[2];

    switch (op)
    {
    case 0x0: // (LD) Load into VX value in VX ==================
        VRegs[VX] = VRegs[VY];
        break;
    case 0x1: // (OR) Bitwise operation (0, 1) -> 1 =============
        VRegs[VX] = VRegs[VX] | VRegs[VY];
        break;
    case 0x2: // (AND) Bitwise operation (0, 1) -> 0´============
        VRegs[VX] = VRegs[VX] & VRegs[VY];
        break;
    case 0x3: // (XOR) Bitwise operation (1, 1) -> 0 ============
        VRegs[VX] = VRegs[VX] ^ VRegs[VY];
        break;
    case 0x4: // (ADD) Add VX with it self with VY using Carry ==
        if (VRegs[VX] + VRegs[VY] > 0x255 || VRegs[VX] + VRegs[VY] < 0x0)
        {
            VRegs[15] = 0x1;
            VRegs[VX] += VRegs[VY];
        }
        break;
    case 0x5: // (SUB) Add VX with it self with VY using Carry =
        VRegs[VX] -= VRegs[VY];
        VRegs[15] = VRegs[VX] > VRegs[VY] ? 0x1 : 0x0;

        break;
    case 0x6: // (SHR) Check least significant bit in VX, if so VF = 1
        if ((~(VRegs[VX]) & 0x00000001) == 0x0)
        {
            VRegs[15] = 0x1;
        }

        break;
    case 0x7: // (SUBN) Sub VX with VY, if VX ¿ VY then VF = 1 =
        VRegs[VX] -= VRegs[VY];
        VRegs[15] = VRegs[VX] < VRegs[VY] ? 0x1 : 0x0;

        break;
    case 0xE: // (SHR) Check most significant bit in VX, if so VF = 1
        if ((~(VRegs[VX]) & 0x10000000) == 0x0)
        {
            VRegs[15] = 0x1;
        }
        break;
    default: // (XXX) Non exist function treatment ===============
        break;
    }
    return 0x0;
}
uint16_t CPU::Op9()
{
    // (SNE) If not, VX is different of VY =======================
    uint8_t VX = ParamsV[0];
    uint8_t VY = ParamsV[1];

    if ((VRegs[VX] - VRegs[VY]) != 0x0)
    {
        PC+=2;
    }
    return 0x0;
}

u_int16_t CPU::OpA()
{
    // (LD) Loads into register I the address
    uint16_t addr = ParamsV[0] | ParamsV[1] | ParamsV[2];

    I = addr;
    return 0x0;
}
u_int16_t CPU::OpB()
{
    // (JP) Set the program counter at addres in V0 with address parsed
    uint16_t addr = ParamsV[0] | ParamsV[1] | ParamsV[2];

    PC = VRegs[0] + addr;
    return 0x0;
}
u_int16_t CPU::OpC()
{   
    // (RND) Generate a number between 0 and 255 and add with kk
    uint8_t VX = ParamsV[0];
    uint8_t byteVal = ParamsV[1] | ParamsV[2];

    GenerateRND();
    uint8_t RAND = ListOld[ListOld.size() - 1];

    VRegs[VX] = RAND + byteVal;
    return 0x0;
}
u_int16_t CPU::OpD()
{
    uint8_t height = ParamsV[2];
    uint8_t x = ParamsV[0];
    uint8_t y = ParamsV[1];
    uint8_t addr;

    for (uint8_t inc = 1; inc < height; inc++)
    {
        addr = y * x * inc;
        bus->Write_Mem(addr, DevicesConn::FrameBuffer, 0x1);
    }
}
u_int16_t CPU::OpE()
{
    
}
u_int16_t CPU::OpF()
{
    
}

uint8_t CPU::GenerateRND() // PSEUDO ALGORITHMICS ( LINEAR CONGRUENT )
{
    // to add later
}