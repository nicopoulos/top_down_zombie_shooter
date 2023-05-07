#include "engine.h"
#include "_graphics.h"
#include "_audio.h"
#include "_physics.h"


#include <SDL2/SDL.h>

int engine_init()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    graphics_init();
    audio_init();
    return 0;
}

int engine_quit()
{
    //SDL_Quit();
    return 0;
}


