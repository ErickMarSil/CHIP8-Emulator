#include <iostream>

using namespace std;

typedef char uint8; // byte type variable
typedef uint8 uint16[2];  // 16 bytes type
typedef uint8 uint16[3]; // 32 bytes type

struct CPU{
    Registers* registers;
    
};
struct Registers{
    uint8* PC[2]; // Program counter
    uint8* IR[2]; // Index Register
    uint8* SP; // Stack Pointer
    uint8* DT; // Delay timer
    uint8* ST; // Sound timer
    uint8* DB; // Display Buffer

    // generic registers
    uint8* V0;
    uint8* V1;
    uint8* V2;
    uint8* V3;
    uint8* V4;
    uint8* V5;
    uint8* V6;
    uint8* V7;
    uint8* V8;
    uint8* V9;
    uint8* VA;
    uint8* VB;
    uint8* VC;
    uint8* VD;
    uint8* VE;
    uint8* VF;

    void init_registers(){

    }
};