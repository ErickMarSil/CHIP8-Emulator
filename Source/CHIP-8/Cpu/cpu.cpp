#include <iostream>

using namespace std;

typedef uint8 = char; // byte type variable
typedef uint16[16]; // 16 bytes type
typedef uint16[32]; // 32 bytes type

CPU get_cpu(){
    CPU newCpu = new CPU; // creates new cpu object
    return newCpu; // return cpu objects
}

private: struct CPU{

}
private: struct Registers{
    uint8* PC[4]; // Program counter
    uint8* IR[2]; // Index Register
    uint8* SP = 0x0; // Stack Pointer

}