#pragma once

#include <SDL2/SDL.h>
#include <cstdint>
#include <string>
#include <vector>

#ifndef CHIP_8
#define CHIP_8

class Memory
{
    private:
        uint8_t RAM[4096];

    public:
        constexpr uint8_t* Get_Pointer(uint8_t addr);

        void Start_Mem();
        void Clear_Mem();
        uint16_t Fetch_Byte(uint8_t addr);
        void Write_Byte(uint8_t addr, uint8_t content);

        void Load_Font();
        int Load_Script(char path[]);
};
class Bus
{
    private:
        Memory* mem = nullptr;
        uint8_t* STACK[64] = {nullptr};
        uint8_t* FRAMEBUFFER[1024] = {nullptr};

    public:
        Bus(Memory* memRef);

        void ConnMem();
        uint8_t Fetch_Byte(uint8_t addr, int device);
        void Write_Byte(uint8_t addr, int device, uint8_t content);
};
class Cpu
{
    private:
        Bus* bus = nullptr;

    public:
        Cpu(Bus* busRef);

        // MAIN 
            void Reset();

        // ALL CPU REGISTER IN CPU CHIP-8
            uint8_t VRegs[16]; // Register V0 to VF
            uint16_t I; // Register "Index Register"
            uint8_t SP; // Register "Stack Pointer"
            uint8_t DT; // Register "Delay Timer"
            uint8_t ST; // Register "Sounder Timer"
            uint16_t PC;// Register "Pointer Counter"

        // OPCODES FUNCTION DECLARATION
            uint16_t Op0(); uint16_t Op1(); uint16_t Op2(); uint16_t Op3(); 
            uint16_t Op4(); uint16_t Op5(); uint16_t Op6(); uint16_t Op7(); 
            uint16_t Op8(); uint16_t Op9(); uint16_t OpA(); uint16_t OpB(); 
            uint16_t OpC(); uint16_t OpD(); uint16_t OpE(); uint16_t OpF();

        // FUNCTIONS CALLERS/PARAMTES
            bool Execute();
            uint16_t Fetch();

            uint8_t ParamsV[3];
            uint8_t FunctI;
            uint8_t Clock;

        // RANDOM stuffs for the cpu
            uint8_t GenerateRND();
            std::vector<uint8_t>ListOld;
};
class Chip8
{
    private:
        Memory* mem;
        Cpu* cpu;
        Bus* bus;

    public:
        bool Init_Chip8(char* argsv[]);
        Cpu* Get_CpuPtr();
};
#endif

#ifndef SDL_PROPS
#define SDL_PROPS

class Screen
{
    private:
        bool trigged = false;
        Cpu* cpu = nullptr;

    public:
        Screen(Cpu* cpuRef);

        uint32_t Devices_Flags = (SDL_INIT_VIDEO);
        SDL_Window* window;
        SDL_Renderer* render;

        struct ScreenProps
        {
            char* screen_title;
            int screen_width;
            int screen_height;
            int screen_pos_x;
            int screen_pos_y;

            int aspect_ratio = 10;

            uint32_t bg_color = 0x0;
            uint32_t fg_color = 0x0;
        };

        bool Init_Screen();
        void Run_screen();
};

#endif