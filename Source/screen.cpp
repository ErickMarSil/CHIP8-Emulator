#include <iostream>
#include <SDL2/SDL.h>

#include "screen.hpp"
#include "bus.hpp"

SCREEN::SCREEN(BUS* busRef)
{
    
    // Window constraints --------------
    configs.screen_title = "CHIP-8";
    configs.screen_width_x = 64;
    configs.screen_height_y = 32;
    configs.screen_position_y = 0;
    configs.screen_position_x = 0;

    // Window setups flags -------------
    Uint32 FlagsWindow = (SDL_WINDOW_SHOWN);

    // Render setups flags -------------
    Uint32 FlagsRender = (SDL_RENDERER_ACCELERATED);

    bus = busRef;

    // Set the top address in the lookup
    lookup = 0x128;
    Init_Screen();


    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Impossible to initialize: %s", SDL_GetError());
        return;
    }
    SDL_Quit();
}

void SCREEN::Init_Screen()
{
    Reset();

    // Set the black window
        window = SDL_CreateWindow
        (
            configs.screen_title,
            configs.screen_position_x,
            configs.screen_position_y,
            configs.screen_height_y,
            configs.screen_width_x,
            configs.FlagsWindow
        );

    // Set the render
        render = SDL_CreateRenderer(window, 1, configs.FlagsRender);
        SDL_SetRenderDrawColor(render, 0x255, 0x255, 0x255, 0x0);

    while (!close)
    {
        SDL_RenderPresent(render);
    }
}

void SCREEN::Reset()
{
    // Clean all pixels in screen
    for (uint8_t& i : SCREEN::pixels) {i = 0x0;}

    // Clear in mnemory address all framebuffer
    for (uint8_t inc; inc < 0x160; inc+=0x1)
    {
        uint8_t addr = lookup + inc;
        bus->Write_Mem(addr, DevicesConn::FrameBuffer, 0x0);
    }
}

void SCREEN::ReadBuffer()
{
    // Setting all pixels values in memory to pixels arr variable (make it easier)
    for (uint8_t inc = 0x0; inc < 0x160; inc += 0x1)
    {
        uint8_t addr = lookup + inc;
        pixels[inc] = bus->Fetch_Mem(addr, DevicesConn::FrameBuffer);
    }
}

void SCREEN::Print()
{
    ReadBuffer();
    int x_coord;
    int y_coord;
    int ind = 1;

    for (uint8_t& pixel : pixels)
    {
        // Calculate relative position
        x_coord = ind % configs.screen_width_x; // relative index at X axis
        y_coord = std::floor(ind / configs.screen_height_y); // relative index at Y axis

        // Draw a 1:1 square in the square and print it
        SDL_Rect square = {1, 1, x_coord, y_coord};
        SDL_RenderFillRect(render, &square);

        ind++;
        Print();
    }
}