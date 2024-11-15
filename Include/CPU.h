#include <cstdint>
#include <string>

class CPU{
    public:
        CPU();
        ~CPU();

        int8_t VRegs[16]; /* Register V0 to VF */
        uint16_t IR; /* Register "Index Register" */
        uint8_t SP; /* Register "Stack Pointer" */
        uint8_t DT; /* Register "Delay Timer" */
        uint8_t ST; /* Register "Sounder Timer" */
        uint8_t PC; /* Register "Pointer Counter" */

        /*OPCODES FUNCTION DECLARATION*/
        uint16_t SYS();  uint16_t CLS(); uint16_t RET();  uint16_t JP(); 
        uint16_t CALL(); uint16_t SE();  uint16_t SEN();  uint16_t LD();
        uint16_t ADD();  uint16_t OR();  uint16_t AND();  uint16_t XOR(); 
        uint16_t SUB();  uint16_t SHR(); uint16_t SUBN(); uint16_t SHL();
        uint16_t SNE();

        0nnn - SYS addr
        00E0 - CLS 
        00EE - RET
        1nnn - JP addr
        2nnn - CALL addr
        3xkk - SE Vx, byte
        4xkk - SNE Vx, byte
        5xy0 - SE Vx, Vy
        6xkk - LD Vx, byte
        7xkk - ADD Vx, byte
        8xy0 - LD Vx, Vy
        8xy1 - OR Vx, Vy
        8xy2 - AND Vx, Vy
        8xy3 - XOR Vx, Vy
        8xy4 - ADD Vx, Vy
        8xy5 - SUB Vx, Vy
        8xy6 - SHR Vx {, Vy}
        8xy7 - SUBN Vx, Vy
        8xyE - SHL Vx {, Vy}
        9xy0 - SNE Vx, Vy

        /*OPCODE TABLE FUNCTIONS*/
        uint16_t* TABLE[20];
}