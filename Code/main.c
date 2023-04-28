#include <stdio.h>

#include "Engine/engine.h"
#include "game.h"

int main()
{
    engine_init();

    game();


    engine_quit(); // doesn't do anything

    return 0;
}