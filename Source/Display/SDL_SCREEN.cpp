#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

struct{
    u_int32_t flg_video = SDL_INIT_VIDEO;
    u_int32_t flg_audio = SDL_INIT_AUDIO;
    u_int32_t flg_controller = SDL_INIT_GAMECONTROLLER;
} flags_sdl;

struct{
    
} window_constraints;

bool init_sdl_subsystem(){
    u_int32_t result_flag = (
        flags_sdl.flg_video | flags_sdl.flg_audio | flags_sdl.flg_controller
    );
    return SDL_Init(result_flag) > 0;
}

bool setup(){
    bool result_initialize = false;
    // init screen config by SDL
    init_sdl_subsystem();
    // return screen config well done
    return result_initialize;
}