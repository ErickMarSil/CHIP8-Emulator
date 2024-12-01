#pragma once

#include <vector>
#include <iostream>
#include <cstdint>

#include "memory.hpp"

//Memory 4K======================
#define MEMORY_START        0x00
#define MEMORY_END          0x7F
//Framebuffer====================
#define FRAMEBUFFER_START   0x80
#define FRAMEBUFFER_END     0x9F
//Stack 64B =====================
#define STACK_START         0xA0
#define STACK_END           0xA0
//Keyboard state=================
#define KEYBOARD_START      0xA1
#define KEYBOARD_END        0xA1
//Control data===================
#define CONTROLDATA_START   0xA2
#define CONTROLDATA_END     0xA2
//===============================

enum class DevicesConn 
{
    Heap = 0,
    FrameBuffer = 1,
    Stack = 2,
    KeyBoard = 3,
    ControllData = 4
};

class BUS
{
    private:
        MEMORY* mem;

        struct MemLocations
        {
            DevicesConn deviceType;
            int start;
            int end;
            uint8_t* Slots = nullptr;
        };
        

    public:
        BUS(MEMORY* memRef);
        ~BUS();

        // Set up the mem pointer class
        void ConnectMem();

        uint8_t Fetch_Mem(uint8_t addr, DevicesConn deviceT);
        void Write_Mem(uint8_t& addr, DevicesConn deviceT, uint8_t data);

        // List with all memorys types
        std::vector<MemLocations> Locations = {};
};