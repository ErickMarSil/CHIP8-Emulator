#include <cstdint>
#include <MEMORY_H.h>

#ifndef BUS_H
#define BUS_H

public:
    enum DevicesConn:
        Stack,
        Heap,
        FrameBuffer,
        KeyBoard,
        ControllData
    
    LIMIT_STACK = ;
    LIMIT_HEAP = ;
    LIMIT_FRAME_BUFFER = ;
    LIMIT_KEY_BOARD = ;
    LIMIT_CONTROLL_DATA = ;

class BUS{
    private:
        MEMORY* Mem = nullptr;
    public:
        /* Limits address for each device */
        /* addrStack, addrHeap, addrFrameBuffer, addrKeyBoard, addrControllData */
        uint16_t* addressLimits[5] = nullptr;

        /* Init all limits and conecnt to memory */
        void InitBus();

        /* Set up the mem pointer class */
        void ConnectMem();

        uint8_t Fetch_Mem(uint16_t& addr, DeviceConn deviceT);
        void Write_Mem(uint16_t& addr, DeviceConn deviceT, uint16_t data);
}

#endif