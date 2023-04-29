#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include "_components.h"
// API
int graphics_init();

int graphics_quit();



typedef struct camera_t
{
    double vpx_per_meter;
    vector_t position;

} camera_t;

extern camera_t camera;

int camera_zoom(double factor);


int camera_set_zoom(double zoom);




void show_buffer();

int clear_buffer();

SDL_Texture* load_texture(const char* file);

int draw_world_element(const transform_t* transform, const spritesheet_t* spritesheet);

#endif