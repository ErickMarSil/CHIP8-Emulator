#pragma once
#include <cstdint>
#include <vector>

class CPU
{
    private:
        BUS bus;

    public:
        CPU();
        ~CPU();

        uint8_t VRegs[16]; // Register V0 to VF
        uint16_t I; // Register "Index Register"
        uint8_t SP; // Register "Stack Pointer"
        uint8_t DT; // Register "Delay Timer"
        uint8_t ST; // Register "Sounder Timer"
        uint16_t PC;// Register "Pointer Counter"

        /*OPCODES FUNCTION DECLARATION*/
            uint16_t Op0();
            uint16_t Op1();
            uint16_t Op2();
            uint16_t Op3();
            uint16_t Op4();
            uint16_t Op5();
            uint16_t Op6();
            uint16_t Op7();
            uint16_t Op8();
            uint16_t Op9();

        // FUNCTIONS CALLERS/PARAMTES
            bool Execute(uint8_t& Clock);
            uint16_t Fetch();

            uint8_t ParamsV[3];
            uint8_t FunctI;
            uint8_t Clock;

        // OPCODE TABLE FUNCTIONS
            std::vector<uint16_t(*)(void)> OPTable;

        // CLOCK functions request and deecrement
            uint8_t RequestClock();
            uint8_t ReduceClock(uint8_t amountClock = 3);
};