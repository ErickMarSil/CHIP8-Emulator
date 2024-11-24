#include <iostream>
#include "SCREEN.h"
#include "BUS.h"
#include <SDL2/SDL.h>

struct ScreenProps{
    public:
        // Window constraints --------------
        int screen_width_y = 60;
        int screen_height_x = 30;
        int screen_position_y = 0;
        int screen_position_x = 0;

        char* screen_title;

        // Window setups flags -------------
        Uint32 FlagsWindow = (SDL_WINDOW_OPENGL);

        // Render setups flags -------------
        Uint32 FlagsRender = (SDL_WINDOW_OPENGL);
};

SCREEN::SCREEN()
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        // Set the black window
        window = SDL_CreateWindow
        (
            configs.screen_title,
            configs.screen_position_x,
            configs.screen_position_y,
            configs.screen_height_x,
            configs.screen_width_y,
            configs.FlagsWindow
        );

        // Set the render
        render = SDL_CreateRenderer
        (
            window,
            -1,
            configs.FlagsRender
        );
        SDL_SetRenderDrawColor
        (
            render,
            0x0,
            0x0,
            0x0,
            0x0
        );
    }
    Init();
}

void SCREEN::Init()
{
    Reset();
    uint8_t addr = 0x128;
    bus.Write_Mem(addr, DevicesConn::FrameBuffer);
}

void SCREEN::Reset()
{
    for (uint8_t& i : SCREEN::pixels) {i = 0x0;}
}

void SCREEN::Print()
{
    uint8_t ep; // (existing pixel) Representative pixel to (WARNING: CHANGING AFTER)
    for (uint8_t& i : SCREEN::pixels) 
    {
        uint8_t state = 
        (
            (bool)(i == 0x1 | ep == 0x1) | 
            (bool)(i == 0x1 | ep == 0x0) | 
            (bool)(i == 0x0 | ep == 0x1) | 
            (bool)(i == 0x0 | ep == 0x0)
        );

        switch (state & 0b1111)
        {
        case 0b0001: // (CHECK) pixel = white and action = white
            // Set (vf = 0x1)
            // Set (pixel = 0x0)
            break;
        case 0b0010: // (CHECK) pixel = white and action = black
            // Set (vf = 0x0)
            // Set (pixel - 0x1)
            break;
        case 0b0100: // (CHECK) pixel = black and action = white
            // Set (vf = 0x0)
            // Set (pixel = 0x0)
            break;
        case 0b1000: // (CHECK) pixel = black and action = black
            // Set (vf = 0x0)
            // Set (pixel = 0x0)
            break;
        default:
            break;
        }
    }
}

void SCREEN::ReadBuffer()
{
    
}