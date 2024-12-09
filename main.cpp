#include <iostream>
#include <cstdint>

#include <SDL2/SDL.h>

struct WINDOW
{
    private:
        uint8_t win_x = 0;
        uint8_t win_y = 0;
        uint8_t win_h = 32;
        uint8_t win_w = 64;
        uint32_t flags = (SDL_WINDOW_BORDERLESS);

    public:
        SDL_Window* window;
        SDL_Renderer* render;


        WINDOW()
        {
            window = SDL_CreateWindow("CHIP-8", win_x, win_y, win_w, win_h, flags);
            render = SDL_CreateRenderer(window, 0, 0x0);
        };
        void Read_FrameBuffer()
        {
            // Frame buffer
        }
};

struct MEMORY
{
    private:
        uint8_t RAM[4096]; // 4kb ram for entire components'
        uint8_t STACK[64]; // 64b of stack to the memory
        uint8_t DISPLAY[64 * 32]; // 1kb of memory to display'

    public:
        const uint8_t startPointer = 0x200;

        MEMORY(const char *argv)
        {
            uint8_t font[] = 
            {
                0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
                0x20, 0x60, 0x20, 0x20, 0x70, // 1
                0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
                0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
                0x90, 0x90, 0xF0, 0x10, 0x10, // 4
                0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
                0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
                0xF0, 0x10, 0x20, 0x40, 0x40, // 7
                0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
                0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
                0xF0, 0x90, 0xF0, 0x90, 0x90, // A
                0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
                0xF0, 0x80, 0x80, 0x80, 0xF0, // C
                0xE0, 0x90, 0x90, 0x90, 0xE0, // D
                0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
                0xF0, 0x80, 0xF0, 0x80, 0x80  // F
            };
            
            memcpy(RAM, font, sizeof(font));
            
            FILE* file = fopen(argv, "rb");
            if (file == NULL)
            {
                std::cout << "Not possible read the file! Check file path" << "\n";
                return;
            }

            fseek(file, 0, SEEK_END);
            long fileLen = ftell(file);
            if (fileLen > 1024)
            {
                std::cout << "" << "\n";
                return;
            }
            fseek(file, 0, SEEK_SET);

            size_t bytes = fread(&RAM[startPointer], 1, fileLen, file);
    };
    void ResetMem()
    {
        for (uint8_t& i : STACK){i = 0x0;}
        for (uint8_t& i : DISPLAY){i = 0x0;}
    }
    void WriteStack(uint8_t addr, uint8_t data){STACK[addr] = data;}
    uint8_t FetchStack(uint8_t addr){return STACK[addr];}
    uint8_t FetchHeap(uint8_t addr){return RAM[addr];}
};
struct CPU
{
    private:
        MEMORY* mem;

        uint8_t VR[16]; // V register from V0 -> VF
        uint16_t I; // Index Register
        uint16_t PC; // Program counter
        uint8_t TR; // Time register
        uint8_t SR; // Sound Register

        uint8_t Opcode; // Opcode to be executed
        uint8_t ArgsBytes[3]; // Arguments to this opcode

    public:
        CPU(MEMORY* memRef)
        {
            mem = memRef;
            PC = mem->startPointer;
            I, TR, SR = 0x0;

            for (uint8_t& i: VR){i = 0x0;}
            for (uint8_t& i: ArgsBytes){i = 0x0;}
        }

        void FetchArgs()
        {
            Opcode = (mem->FetchHeap((PC >> 16) & 0x0F) >> 8) & 0xFF; // reads first byte

            // Reads all the bytes and divide thebn
            ArgsBytes[0] = (mem->FetchHeap((PC >> 16) & 0x0F) << 8) & 0xFF;
            ArgsBytes[1] = (mem->FetchHeap((PC << 16) & 0xF0) >> 8) & 0xFF;
            ArgsBytes[2] = (mem->FetchHeap((PC << 16) & 0xF0) << 8) & 0xFF;

            PC += 2;
        }
        void Execute()
        {
            FetchArgs();
            std::cout << "the Opcode is:" << Opcode << "\n";
        }
};

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Require to a file to read!" << "\n";
        return 1;
    }
    MEMORY mem(argv[1]);
    CPU cpu(&mem);
    for (int i = 0; i < 1024; i++)
    {
        cpu.Execute();
    }
    return 0;
}