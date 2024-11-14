#include <iostream>
#include <cstdint>
#include <BUS_H.h>
#include <MEMORY_H.h>


class BUS{
    uint16_t* addressLimits[5];

    void InitBus(){
        BUS::addressLimits[0] = 
    }
    void ConnectMem(){

    }
    uint8_t Fetch_Mem(uint16_t& addr, DeviceConn deviceT){

    }
    void Write_Mem(uint16_t& addr, DeviceConn deviceT, uint16_t data){

    }
}