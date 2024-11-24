#pragma once
#include <cstdint>
#include <MEMORY.h>

enum class DevicesConn 
{
    Stack = 0,
    Heap = 1,
    FrameBuffer = 2,
    KeyBoard = 3,
    ControllData = 4
};

class BUS
{
    private:
        MEMORY* Mem;

    public:
        BUS(MEMORY* memRef);
        ~BUS();
        
        // Limits address for each device
        // addrStack, addrHeap, addrFrameBuffer, addrKeyBoard, addrControllData
        uint16_t addressLimits[5][2];

        /* Set up the mem pointer class */
        void ConnectMem();

        uint8_t Fetch_Mem(uint8_t addr, DevicesConn deviceT);
        void Write_Mem(uint8_t& addr, DevicesConn deviceT, uint8_t data);
};