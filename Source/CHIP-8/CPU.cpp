#include <iostream>
#include <random>
#include <vector>
#include "CPU.h"
#include "BUS.h"

CPU::CPU()
{
    Reset();

    CPU::OPTable = 
    {
        &CPU::Op0, &CPU::Op1, &CPU::Op2, &CPU::Op3,
        &CPU::Op4, &CPU::Op5, &CPU::Op6, &CPU::Op7,
        &CPU::Op8, &CPU::Op9, &CPU::OpA, &CPU::OpB,
        &CPU::OpC, &CPU::OpD, &CPU::OpE, &CPU::OpF
    };
}

void SetBus(BUS& busInsntance)
{
    BUS bus = busInsntance;
}

void CPU::Reset()
{
    // Set program counter in top of the heap in 0x200
    // Set stack pointer in top of the stack 0x 0x160
    PC = 0x200;
    SP = 0x160;
    FunctI = 0x0;
    for (uint8_t& i : ParamsV){i = 0x0;}

    I, PC = 0x00;
    SP, DT, ST = 0x0;

    for (uint8_t& i : VRegs){i = 0x0;}

    ListOld = {0x1};
}

bool CPU::Execute()
{
    if(Clock == 0)
    {
        // Fetch functions and set bytes paramters
        Fetch();

        if(FunctI <= (sizeof(OPTable) / 4))
        {
            // Request a clock
            RequestClock();

            // Call function in opcode
            OPTable[FunctI]();

            // Reduce Clock
            ReduceClock();
        }
        else
        {
            // Raises an error in console
        }
    }
}

// Fetch 2 bytes from memory =========================================

uint16_t CPU::Fetch()
{
    uint8_t entire[2] = 
    {
        bus.Fetch_Mem((PC >> 8), DevicesConn::Heap),
        bus.Fetch_Mem((PC << 8), DevicesConn::Heap)
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
uint8_t CPU::ReduceClock(uint8_t amountClock = 3)
{
    if (Clock + 3 >= 3)
    {
        Clock -= 3;
    }
}


// OPCODE FUNCTION DECLARED (ALU) ===================================
uint16_t CPU::Op0()
{
    uint8_t op = (FunctI >> 4) & 0b0000;

    switch (op)
    {
    case 0x0E0: // (CLS) Clear screen in frame buffer
        for (uint8_t i; i < 0x160; i += 0x1)
        {
            uint8_t a = 0x0;
            bus.Write_Mem(i, DevicesConn::FrameBuffer, 0x00, SP);
        }
        break;
    case 0x0EE: // (RET) Retunr to caller point
        PC = 0x200;
        SP -= 0x1;
        return 0x0;
        break;
    default:
        break;
    }
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
        PC++;
        return 0x0;
    };
}

uint16_t CPU::Op4() // (SNE) If not VX equal to kk(byte) =========
{
    uint8_t VX = ParamsV[0];
    uint8_t byteVal = ParamsV[1] | ParamsV[2];

    if((VX - byteVal) != 0x0)
    {
        PC++;
        return 0x0;
    }
    PC++;
}
uint16_t CPU::Op5()
{
    // (SE) If VX is equal to VY
    uint8_t VX = ParamsV[1];
    uint8_t VY = ParamsV[2];

    if((VRegs[VX] - VRegs[VY]) == 0x0)
    {
        PC++;
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
        return 0x0;
        break;
    case 0x1: // (OR) Bitwise operation (0, 1) -> 1 =============
        VRegs[VX] = VRegs[VX] | VRegs[VY];
        return 0x0;
        break;
    case 0x2: // (AND) Bitwise operation (0, 1) -> 0´============
        VRegs[VX] = VRegs[VX] & VRegs[VY];
        return 0x0;
        break;
    case 0x3: // (XOR) Bitwise operation (1, 1) -> 0 ============
        VRegs[VX] = VRegs[VX] ^ VRegs[VY];
        return 0x0;
        break;
    case 0x4: // (ADD) Add VX with it self with VY using Carry ==
        if (VRegs[VX] + VRegs[VY] > 0x255 || VRegs[VX] + VRegs[VY] < 0x0)
        {
            VRegs[15] = 0x1;
            VRegs[VX] += VRegs[VY];
        }
        return 0x0;
        break;
    case 0x5: // (SUB) Add VX with it self with VY using Carry =
        VRegs[VX] -= VRegs[VY];
        VRegs[15] = VRegs[VX] > VRegs[VY] ? 0x1 : 0x0;
        
        return 0x0;
        break;
    case 0x6: // (SHR) Check least significant bit in VX, if so VF = 1
        if ((~(VRegs[VX]) & 0x00000001) == 0x0)
        {
            VRegs[15] = 0x1;
        }

        return 0x0;
        break;
    case 0x7: // (SUBN) Sub VX with VY, if VX ¿ VY then VF = 1 =
        VRegs[VX] -= VRegs[VY];
        VRegs[15] = VRegs[VX] < VRegs[VY] ? 0x1 : 0x0;

        return 0x0;
        break;
    case 0xE: // (SHR) Check most significant bit in VX, if so VF = 1
        if ((~(VRegs[VX]) & 0x10000000) == 0x0)
        {
            VRegs[15] = 0x1;
        }
        return 0x0;
        break;
    default: // (XXX) Non exist function treatment ===============
        break;
    }
}
uint16_t CPU::Op9()
{
    // (SNE) If not, VX is different of VY =======================
    uint8_t VX = ParamsV[0];
    uint8_t VY = ParamsV[1];

    if ((VRegs[VX] - VRegs[VY]) != 0x0)
    {
        return 0x0;
    }
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
    // (DRW) Draw 
    uint8_t VX = ParamsV[0];
    uint8_t VY = ParamsV[1];

    I = VRegs[VX] | VRegs[VY];
    VRegs[15] = 0x1;
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