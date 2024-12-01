#include <iostream>
#include <string>
#include <SDL2/SDL.h>

#include "main.hpp"

// SCREEN SECTION

bool Screen::Init_Screen()
{
    ScreenProps config = 
    {
        "CHIP-8", 64, 32, 0, 0, 10, 0x0, 0x0
    };

    window = SDL_CreateWindow
    (
        config.screen_title,
        config.screen_pos_x,
        config.screen_pos_y,
        config.screen_width * config.aspect_ratio,
        config.screen_height * config.aspect_ratio,
        NULL
    );
    if (window == NULL)
    {
        std::cout << "Error in window intialize, please run again!" << "\n";
        SDL_Quit();
        return false;
    }

    render = SDL_CreateRenderer
    (
        window, 0, NULL
    );
    if (render == NULL)
    {
        std::cout << "Error in render intialize, please run again!" << "\n";
        SDL_Quit();
        return false;
    }
}

void Screen::Run_screen()
{
    trigged = true;
    while (trigged == true)
    {
        SDL_RenderClear(render);
    }
}

// MEMORY SECTION

constexpr uint8_t* Memory::Get_Pointer(uint8_t addr){return &Memory::RAM[addr];}
void Memory::Start_Mem(){Memory::Clear_Mem();}
void Memory::Clear_Mem()
{
    for (uint8_t &i : Memory::RAM){i = 0x0;}
}
uint16_t Memory::Fetch_Byte(uint8_t addr)
{
    if (addr > 4096)
    {
        std::cout << "overload memory, address (0x%s) not recognized!" << "\n";
        return;
    }
    return Memory::RAM[addr];
}
void Memory::Write_Byte(uint8_t addr, uint8_t content)
{
    if (addr > 4096)
    {
        std::cout << "overload memory, address (0x%s) not recognized!" << "\n";
        return;
    }
    Memory::RAM[addr] = content;
}

void Memory::Load_Font()
{
    uint8_t font[80] =
    {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };
    for (uint8_t inc = 0x0; inc < sizeof(font); inc++)
    {
        Write_Byte(0x0 + inc, font[inc]);
    }
}

// BUS SECTION

Bus::Bus(Memory* memRef)
{
    Bus::mem = memRef;
}
void Bus::ConnMem()
{
    mem->Start_Mem();

    // Start the pointer at arrays (Stack)
    uint8_t inc = 0x0;
    for (uint8_t* i : Bus::STACK)
    {
        uint8_t addr = 0x160 + inc;
        i = mem->Get_Pointer(addr);
    }
    // Start the pointer at arrays (Framebuffer)
    uint8_t inc = 0x0;
    for (uint8_t* i : Bus::FRAMEBUFFER)
    {
        uint8_t addr = 0x160 + inc;
        i = mem->Get_Pointer(0x128);
    }
}
uint8_t Bus::Fetch_Byte(uint8_t addr, int device)
{
    switch (device)
    {
    case 0: return *Bus::STACK[addr];
        break;
    case 1: return *Bus::FRAMEBUFFER[addr];
        break;
    default: return mem->Fetch_Byte(addr);
        break;
    }
}

void Bus::Write_Byte(uint8_t addr, int device, uint8_t content)
{
    switch (device)
    {
    case 0: *Bus::STACK[addr] = content;
        break;
    case 1: *Bus::FRAMEBUFFER[addr] = content;
        break;
    default:
        break;
    }
    return;
}

// Cpu SECTION

Cpu::Cpu(Bus* busRef)
{
    Reset();
    bus = busRef;
}

void Cpu::Reset()
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

bool Chip8::Init_Chip8(std::string path_file_argument)
{
    Memory mem;
    Bus bus(&mem);
    Cpu Cpu(&bus);
}

bool Cpu::Execute()
{
    // Fetch functions and set bytes paramters
    Fetch();

    // TEMPORARILY ----
    if( /* FunctI <= (sizeof(OPTable) / 4) */ FunctI <= 0xF)
    {
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
        return true;
    }
    else
    {
        // raises an error and return
        return false;
    }
}

uint16_t Cpu::Fetch()
{
    uint8_t entire[2] = 
    {
        // -1 Represents the heap to Program Counter
        bus->Fetch_Byte((PC >> 8) & 0xFF, -1),
        bus->Fetch_Byte((PC << 8) & 0xFF, -1)
    };
    FunctI = (entire[0] >> 4) & 0b0000;

    ParamsV[0] = (entire[0] << 4);
    ParamsV[1] = (entire[1] >> 4);
    ParamsV[2] = (entire[1] << 4);

    return 0x0;
}

uint16_t Cpu::Op0()
{
    uint8_t op = (FunctI >> 4) & 0b0000;

    switch (op)
    {
    case 0x0E0: // (CLS) Clear screen in frame buffer
        for (uint8_t inc; inc < 0x160; inc += 0x1)
        {
            uint8_t addr = inc + 0x128;
            bus->Write_Byte(addr, -1, 0x00);
            SP++;
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

uint16_t Cpu::Op1() // (JP) Jumps to cetain address in memory ======
{
    uint16_t addr = ParamsV[0] | ParamsV[1] | ParamsV[2];

    PC = addr;
    return 0x0;
}
uint16_t Cpu::Op2() // (CALL) Call a cetain label ==================
{
    uint16_t addr = ParamsV[0] | ParamsV[1] | ParamsV[2];

    PC = addr;
    return 0x0;
}

uint16_t Cpu::Op3() // (SE) If VX is equal to kk(byte) ============
{
    uint8_t VX = ParamsV[0];
    uint8_t byteVal = ParamsV[1] | ParamsV[2];

    if((VX - byteVal) == 0x0)
    {
        PC+=2;
    };
    return 0x0;
}

uint16_t Cpu::Op4() // (SNE) If not VX equal to kk(byte) =========
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
uint16_t Cpu::Op5()
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
uint16_t Cpu::Op6()
{
    // (LD) Load into register VX the value kk(byte) ============
    uint8_t VX = ParamsV[0];
    uint8_t byteVal = ParamsV[1] | ParamsV[2];

    VRegs[VX] = byteVal;
    return 0x0;
}
uint16_t Cpu::Op7()
{
    // (ADD) Add VX register to it self and with kk(byte) =======
    uint8_t VX = ParamsV[0];
    uint8_t byteVal = ParamsV[1] | ParamsV[2];

    VRegs[VX] += byteVal;
    return 0x0;
}
uint16_t Cpu::Op8()
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
uint16_t Cpu::Op9()
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

u_int16_t Cpu::OpA()
{
    // (LD) Loads into register I the address
    uint16_t addr = ParamsV[0] | ParamsV[1] | ParamsV[2];

    I = addr;
    return 0x0;
}
u_int16_t Cpu::OpB()
{
    // (JP) Set the program counter at addres in V0 with address parsed
    uint16_t addr = ParamsV[0] | ParamsV[1] | ParamsV[2];

    PC = VRegs[0] + addr;
    return 0x0;
}
u_int16_t Cpu::OpC()
{   
    // (RND) Generate a number between 0 and 255 and add with kk
    uint8_t VX = ParamsV[0];
    uint8_t byteVal = ParamsV[1] | ParamsV[2];

    GenerateRND();
    uint8_t RAND = ListOld[ListOld.size() - 1];

    VRegs[VX] = RAND + byteVal;
    return 0x0;
}
u_int16_t Cpu::OpD()
{
    uint8_t height = ParamsV[2];
    uint8_t x = ParamsV[0];
    uint8_t y = ParamsV[1];
    uint8_t addr;

    for (uint8_t inc = 1; inc < height; inc++)
    {
        addr = x * y;
        bus->Write_Byte(addr, -1, 0x1);
    }
    return 0x0;
}
u_int16_t Cpu::OpE()
{
    return 0x0;
}
u_int16_t Cpu::OpF()
{
    return 0x0;
}


void Chip8::Run_Chip8()
{
    
}

int main(int args, char* argsv[])
{
    // Initialize the chip 8 structure

    // Initialize the screen
    Screen* screen;
    screen->Init_Screen();
    // screen->Run_screen();
}