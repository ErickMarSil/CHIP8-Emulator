#include <SDL2/SDL.h>
#include "memory.hpp"
#include "cpu.hpp"
#include "bus.hpp"

struct ScreenProps{
    public:
        // Window constraints --------------
        int screen_width_x;
        int screen_height_y;
        int screen_position_y;
        int screen_position_x;

        char* screen_title;

        // Window setups flags -------------
        Uint32 FlagsWindow;

        // Render setups flags -------------
        Uint32 FlagsRender;
};


// SDL variables
ScreenProps configs;
SDL_Window* window;
SDL_Renderer* render;

// System poiter (system projection)
uint8_t* VF; // porpouse: for colision
uint16_t lookup; // similar to stack pointer for screen

// Instaciations of devices
MEMORY mem;
BUS bus(&mem);
CPU cpu(&bus);

bool close; // Trigger to check close and oppen
uint8_t pixels[1024]; // All pixels variable to set