#include <cstdint>
#include <iostream>
#ifndef MEMORY_H
#define MEMORY_H

private:
    constexpr uint64_t MAX_MEMORY = 1024*4;
    constexpr uint64_t MAX_FRAMEBUFFER = 1024;
    constexpr uint8_t  MAX_STACK = 16*2;
    constexpr uint8_t  MAX_KEYBOARDS = 16*2;
    constexpr uint8_t  MAX_CONTROLDATA = 16*2;

public:
    /*Enum others type*/
    enum FETCH_TYPE:
        fFmBuff = &Fetch_FrameBuffer;
        fKeyB = &Fetch_KeyBoard;
        fControllD = &Fetch_ControllData;
    enum WRITE_TYPE:
        wFmBuff = &Write_FrameBuffer;
        wKeyB = &Write_KeyBoard;
        wControllD = &Write_ControllData;

    /*Enum memory type*/
    enum FETCH_MEMORY:
        fRAM = ;
        fSTACK = ;
    enum WRITE_MEMORY:
        fRAM = ;
        fSTACK = ;

    struct MEMORY {
        /*
        RAM slots begin to end 0x0 -> 0x1000 (4096 bytes)
        STACK slots begin 0xEA0 to 0xEFF (32 bytes)
        */
        uint8_t MEMORY::RAM[MAX_MEMORY]; /*RAM or HEAP memory to program it self*/
        uint8_t MEMORY::STACK[MAX_STACK]; /*STACK or WRITE memory to cpu process and fast access*/
        uint8_t MEMORY::FRAMEBUFFER[MAX_FRAMEBUFFER]; /*FRAMEBUFFER or DISPLAY to storage pixels*/
        uint8_t MEMORY::KEYBOARD[MAX_KEYBOARDS]; /*KEYBOARD STATUS or INPUT handle the user inputs*/
        uint8_t MEMORY::CONTROLDATA[MAX_CONTROLDATA]; /**/
        /*
        Clear all memorys types such as RAM, STACK, FRAMEBUFFER
        */
        void Reset_All_Memory();

        /*Reset the Ram/Heap memory setting 0x00 bytes on it*/
        void Reset_Memory();
        /*Reset the Stack memory setting 0x00 bytes on it*/
        void Reset_Stack();
        /*Reset the Framebuffer bucket setting 0x00 bytes on it*/
        void Reset_FrameBuffer();
        /*Reset the Keyboard inputs setting 0x00 bytes on it*/
        void Reset_KeyBoardS();

        /*
            Write/Fetch functions to differents buffer wires
        */
        private:
            void Fetch_FrameBuffer(uint8_t& addr);  void Write_FrameBuffer(uint8_t& addr, uint8_t data);
            void Fetch_KeyBoard(uint8_t& addr);     void Write_KeyBoard(uint8_t& addr, uint8_t data);
            void Fetch_ControllData(uint8_t& addr); void Write_ControllData(uint8_t& addr, uint8_t data);

        /*  Can read byte from others slots:
                * FrameBuffer
                * Keyboard
                * ControlData*/
        uint8_t FetchOthers(SLOTS_TYPE area_type, uint8_t& addr);

        /*  Can write byte from others slots:
                * FrameBuffer
                * Keyboard
                * ControlData*/
        void WriteOthers(SLOTS_TYPE area_type, uint8_t& addr, uint16_t data);


    };

#endif