#include <iostream>
#include "BUS.h"
#include "MEMORY.h"

BUS::BUS()
{
    // Define limits of each devices to call them

    //Memory 4K
    addressLimits[0][0] = 0x00;
    addressLimits[0][1] = 0x128;

    //Framebuffer
    addressLimits[1][0] = addressLimits[0][1] + 1;
    addressLimits[1][1] = 0x160;

    //Stack 64B
    addressLimits[2][0] = addressLimits[1][1] + 1;
    addressLimits[2][1] = 0x161;

    //Keyboard state
    addressLimits[3][0] = addressLimits[2][1] + 1;
    addressLimits[3][1] = 0x162;

    //Control data
    addressLimits[4][0] = addressLimits[3][1] + 1;
    addressLimits[4][1] = 0x162;
}

uint8_t BUS::Fetch_Mem(uint8_t& addr, DevicesConn deviceT)
{
    if (addr >= addressLimits[(int)deviceT][0] && addr <= addressLimits[(int)deviceT][1])
    {
        return Mem.FetchRAM(addr);
    }
}
void BUS::Write_Mem(uint8_t& addr, DevicesConn deviceT, uint8_t data, uint16_t& SP)
{
    if (addr >= addressLimits[(int)deviceT][0] && addr <= addressLimits[(int)deviceT][1])
    {
        Mem.WriteRAM(addr, data);
        if ((int)deviceT == 0)
        {
            SP++;
        }
    }
    return;
}
BUS::~BUS()
{

}