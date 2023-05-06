#include <stdio.h>

#include "Engine/engine.h"
#include "game.h"

SDL_GameController* gamepad;

int main()
{
    if (engine_init())
        return -1;

    gamepad = SDL_GameControllerOpen(0);
    if (gamepad == NULL)
    {
        fprintf(stderr, "%s\n", SDL_GetError());
    }

    game();


    engine_quit(); // doesn't do anything

    return 0;
}