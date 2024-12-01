#pragma once

#include <cstdint>
#include <vector>
#include <stdio.h>

#include "bus.hpp"

class CPU
{
    private:
        BUS* bus;

    public:
        explicit CPU(BUS* busRef);
        ~CPU();

        // MAIN 
        void Reset();

        // ALL CPU REGISTER IN CPU CHIP-8
            uint8_t VRegs[16]; // Register V0 to VF
            uint16_t I; // Register "Index Register"
            uint8_t SP; // Register "Stack Pointer"
            uint8_t DT; // Register "Delay Timer"
            uint8_t ST; // Register "Sounder Timer"
            uint16_t PC;// Register "Pointer Counter"

        // OPCODES FUNCTION DECLARATION
            uint16_t Op0(); uint16_t Op1(); uint16_t Op2(); uint16_t Op3(); 
            uint16_t Op4(); uint16_t Op5(); uint16_t Op6(); uint16_t Op7(); 
            uint16_t Op8(); uint16_t Op9(); uint16_t OpA(); uint16_t OpB(); 
            uint16_t OpC(); uint16_t OpD(); uint16_t OpE(); uint16_t OpF();

        // FUNCTIONS CALLERS/PARAMTES
            bool Execute();
            uint16_t Fetch();

            uint8_t ParamsV[3];
            uint8_t FunctI;
            uint8_t Clock;

        // OPCODE TABLE FUNCTIONS
            // typedef uint16_t(CPU::*op_ptr)();
            // std::vector<op_ptr> OPTable;

        // CLOCK functions request and deecrement
            uint8_t RequestClock();
            uint8_t ReduceClock(uint8_t amountClock);

        // RANDOM stuffs for the cpu
            uint8_t GenerateRND();
            std::vector<uint8_t>ListOld;
};