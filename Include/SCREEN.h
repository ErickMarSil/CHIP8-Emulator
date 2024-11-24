#pragma once

#include <cstdint>
#include <BUS.h>
#include <SDL2/SDL.h>

class SCREEN
{
    private:
        ScreenProps configs;
        SDL_Window* window;
        SDL_Renderer* render;

    public:
        SCREEN();
        ~SCREEN();

        void Init();    // Initialize the screen
        void Reset();   // Reset Screen variables and framebuffer
        void ClearScreen(); // Clear all pixels in screen
        void Print();   // Draw in screen informations
        void ReadBuffer(); // Read from buffer in memory

        uint8_t pixels[1024]; // All pixels variable to set
};