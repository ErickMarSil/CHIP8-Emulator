#include <cstdint>
#include <MEMORY_H.h>

#ifndef BUS_H
#define BUS_H
private:
    /*Enum others type*/
    enum FETCH_TYPE:
        fFmBuff,
        fKeyB,
        fControllD
    enum WRITE_TYPE:
        wFmBuff,
        wKeyB,
        wControllD
    
    MEMORY memory;

public:
    struct BUS{
        uint8_t& RAM = memory.RAM;
        /*
        This BUS is just for memory STACK purpouse and only
        */
        uint8_t Read(uint16_t& addr);
        void Write(uint16_t& addr, uint8_t data);
    };
    struct BUS_O{
        /*
        This BUS is for other devices in allowed_devices
        */
        private:
            void Fetch_FrameBuffer(uint16_t& addr);
            uint8_t Write_FrameBuffer(uint16_t& addr, uint8_t data);
            void Fetch_KeyBoard(uint16_t& addr);
            uint8_t Write_KeyBoard(uint16_t& addr, uint8_t data);
            void Fetch_ControllData(uint16_t& addr);
            uint8_t Write_ControllData(uint16_t& addr, uint8_t data);

        uint16_t (*Write_Funcs[3])() = {Fetch_FrameBuffer, Fetch_KeyBoard, Fetch_ControllData};
        uint16_t (*Fetch_Funcs[3])() = {Write_ControllData, Write_KeyBoard, Write_ControllData};

        uint8_t Read(FETCH_TYPE memT, uint16_t& addr);
        void Write(WRITE_TYPE memT, uint16_t& addr, uint8_t data);
    };
#endif