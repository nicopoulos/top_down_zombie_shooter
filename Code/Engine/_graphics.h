#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include "_components.h"
// API
int graphics_init();

int graphics_quit();


int camera_zoom(double factor);


int camera_set_zoom(double zoom);

void camera_set_position(double x, double y);

void camera_move(double dx, double dy);



void show_buffer();

int set_render_colour(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

int clear_buffer();

SDL_Texture* load_texture(const char* file);

int draw_world_element(const transform_t* transform, const spritesheet_t* spritesheet);

#endif