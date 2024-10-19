#pragma once
#include<SDL.h>
#include<stdio.h>

#include "vertex.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

typedef struct {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;

} display_components_t;

extern int display_pitch;
extern uint32_t* pixel_buffer;

extern display_components_t* setup_sdl_components(display_components_t*);

extern void render_loop(display_components_t*, vertex_t* vertices, size_t count);

extern void draw_grid();
extern void draw_background();
extern void draw_vertex(vertex_t* vertices, size_t count);

extern void cleanup_sdl_components(display_components_t*);