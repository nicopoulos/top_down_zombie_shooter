#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdint.h>
#include <stdbool.h>

#include "_components.h"
#include "_graphics.h"
#include "_audio.h"

// engine functions
int engine_init();

int engine_quit();

// graphics functions
extern int draw_world_element(const transform_t* transform, const spritesheet_t* spritesheet);

#endif
