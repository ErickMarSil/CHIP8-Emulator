#pragma once

#include <cstdint>
#include <SDL2/SDL.h>

#include "bus.hpp"



struct ScreenProps{
    public:
        // Window constraints --------------
        int screen_width_y;
        int screen_height_x;
        int screen_position_y;
        int screen_position_x;

        char* screen_title;

        // Window setups flags -------------
        Uint32 FlagsWindow;

        // Render setups flags -------------
        Uint32 FlagsRender;
};

class SCREEN
{
    private:
        // SDL variables
        ScreenProps configs;
        SDL_Window* window;
        SDL_Renderer* render;

        // System poiter (system projection)
        BUS* bus;   // porpouse: read from memory
        uint8_t* VF; // porpouse: for colision
        uint16_t lookup; // similar to stack pointer for screen

    public:
        SCREEN(BUS* busRef);
        ~SCREEN();

        void Init_Screen(); // Initialize screen it self

        void Reset();   // Reset Screen variables and framebuffer
        void ClearScreen(); // Clear all pixels in screen
        void ReadBuffer(); // Read from buffer in memory
        void Print();   // Draw in screen informations

        uint8_t pixels[1024]; // All pixels variable to set
};