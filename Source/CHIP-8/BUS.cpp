#include <iostream>
#include <cstdint>
#include <BUS_H.h>

struct BUS{
    struct BUS{
        uint8_t Read(uint16_t& addr){

        }
        void Write(uint16_t& addr, uint8_t data){

        }
    };
    struct BUS_O{
        void Fetch_FrameBuffer(uint16_t& addr){
            if (addr >= &FRAMEBUFFER[FRAMEBUFFER.size()-1] && addr <= &FRAMEBUFFER.begin()){
                return FRAMEBUFFER[addr];
            }
        }
        uint8_t Write_FrameBuffer(uint16_t& addr, uint8_t data){
            if (addr >= &FRAMEBUFFER[FRAMEBUFFER.size()-1] && addr <= &FRAMEBUFFER.begin()){
                FRAMEBUFFER[addr] = data;
            }
            return;
        }
        void Fetch_KeyBoard(uint16_t& addr){
            if (addr >= &KEYBOARD[KEYBOARD.size()-1] && addr <= &KEYBOARD.begin()){
                return KEYBOARD[addr];
            }
        }
        uint8_t Write_KeyBoard(uint16_t& addr, uint8_t data){
            if (addr >= &KEYBOARD[KEYBOARD.size()-1] && addr <= &KEYBOARD.begin()){
                KEYBOARD[addr] = data;
            }
            return;
        }
        void Fetch_ControllData(uint16_t& addr){
            if (addr >= &CONTROLDATA[CONTROLDATA.size()-1] && addr <= &CONTROLDATA.begin()){
                return CONTROLDATA[addr];
            }
        }
        uint8_t Write_ControllData(uint16_t& addr, uint8_t data){
            if (addr >= &CONTROLDATA[CONTROLDATA.size()-1] && addr <= &CONTROLDATA.begin()){
                CONTROLDATA[addr] = data;
            }
            return;
        }

        uint16_t (*Write_Funcs[3])() = {Fetch_FrameBuffer, Fetch_KeyBoard, Fetch_ControllData};
        uint16_t (*Fetch_Funcs[3])() = {Write_ControllData, Write_KeyBoard, Write_ControllData};

        uint8_t Read(FETCH_TYPE memT, uint16_t& addr){
            Fetch_Funcs[memT]();
            return;
        }
        void Write(WRITE_TYPE memT, uint16_t& addr, uint8_t data){
            return Write_Funcs[memT]();
        }
    };
};