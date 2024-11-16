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

        uint8_t VRegs[16]; /* Register V0 to VF */
        uint16_t IR; /* Register "Index Register" */
        uint8_t SP; /* Register "Stack Pointer" */
        uint8_t DT; /* Register "Delay Timer" */
        uint8_t ST; /* Register "Sounder Timer" */
        uint16_t* PC; /* Register "Pointer Counter" */

        /*OPCODES FUNCTION DECLARATION*/
        uint16_t SYS (uint16_t addr);               // 0nnn - SYS addr
        uint16_t CLS ();                            // 00E0 - CLS
        uint16_t RET ();                            // 00EE - RET
        uint16_t JP  (uint16_t& addr);              // 1nnn - JP addr
        uint16_t CALL(uint16_t addr);               // 2nnn - CALL addr
        uint16_t SE  (uint8_t VX, uint8_t byte);    // 3xkk - SE Vx, byte
        uint16_t SNE (uint8_t VX, uint8_t byte);    // 4xkk - SNE Vx, byte
        uint16_t SE  (uint8_t VX, uint8_t VY);      // 5xy0 - SE Vx, Vy  
        uint16_t LD  (uint8_t& VX, uint8_t byte);   // 6xkk - LD Vx, byte
        uint16_t ADD (uint8_t& VX, uint8_t byte);   // 7xkk - ADD Vx, byte
        uint16_t LD  (uint8_t& VX, uint8_t VY);     // 8xy0 - LD Vx, Vy 
        uint16_t OR  (uint8_t& VX, uint8_t& VY);    // 8xy1 - OR Vx, Vy 
        uint16_t AND (uint8_t& VX, uint8_t& VY);    // 8xy2 - AND Vx, Vy 
        uint16_t XOR (uint8_t& VX, uint8_t& VY);    // 8xy3 - XOR Vx, Vy 
        uint16_t ADD (uint8_t& VX, uint8_t VY);     // 8xy4 - ADD Vx, Vy 
        uint16_t SUB (uint8_t& VX, uint8_t VY);     // 8xy5 - SUB Vx, Vy 
        uint16_t SHR (uint8_t& VX);                 // 8xy6 - SHR Vx {, Vy}
        uint16_t SUBN(uint8_t& VX, uint8_t VY);     // 8xy7 - SUBN Vx, Vy
        uint16_t SHL (uint8_t& VX);                 // 8xyE - SHL Vx {, Vy}
        uint16_t SNE (uint8_t VX, uint8_t VY);      // 9xy0 - SNE Vx, Vy


        /*Functions to call*/
        bool Execute(uint8_t& Clock);
        void Fetch_Function(uint8_t& PC);
        void Fetch_Params(uint8_t& PC);

        uint8_t FunctionOP = 0x0;

        /*OPCODE TABLE FUNCTIONS*/
        std::vector<uint16_t(*)(void)> OPTable;
};