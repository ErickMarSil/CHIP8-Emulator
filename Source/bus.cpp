#include <vector>
#include <iostream>
#include <cstdint>

#include "bus.hpp"
#include "memory.hpp"

BUS::BUS(MEMORY* memRef)
{
    mem = memRef;

    Locations =
    {
        {DevicesConn::Heap, MEMORY_END, MEMORY_START, &mem->RAM[MEMORY_START]},
        {DevicesConn::FrameBuffer, FRAMEBUFFER_START, FRAMEBUFFER_END, &mem->RAM[FRAMEBUFFER_START]},
        {DevicesConn::Stack, STACK_END, STACK_START, &mem->RAM[STACK_END]},
        {DevicesConn::KeyBoard, KEYBOARD_END, KEYBOARD_START, &mem->RAM[KEYBOARD_END]},
        {DevicesConn::ControllData, CONTROLDATA_END, CONTROLDATA_START, &mem->RAM[CONTROLDATA_END]}
    };

}

uint8_t BUS::Fetch_Mem(uint8_t addr, DevicesConn deviceT)
{
    if(addr >= Locations[(int)deviceT].start && addr <= Locations[(int)deviceT].end)
    {
        return mem->FetchRAM(addr);
    }
    return 0x0;
}
void BUS::Write_Mem(uint8_t& addr, DevicesConn deviceT, uint8_t data)
{
    if(addr >= Locations[(int)deviceT].start && addr <= Locations[(int)deviceT].end)
    {
        mem->WriteRAM(addr, data);
    }
    return;
}