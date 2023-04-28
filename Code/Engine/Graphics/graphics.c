#include "graphics.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

SDL_Window* window;
SDL_Renderer* renderer;

double pixels_per_meter;

int graphics_init()
{
    window = SDL_CreateWindow("hallo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1, 1, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == NULL)
        return -1;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        return -1;

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    return 0;


}

int graphics_quit()
{
    TTF_Quit();
    IMG_Quit();

    if (renderer != NULL)
        SDL_DestroyRenderer(renderer);

    if (window != NULL)
        SDL_DestroyWindow(window);

    printf("C\n");

    return 0;

}