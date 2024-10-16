#include "display.h"

int display_pitch = (int)(WINDOW_WIDTH * sizeof(uint32_t));
uint32_t* pixel_buffer = NULL;

display_components_t* setup_sdl_components(display_components_t* sdl_components) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "There was an error initializing SDL.\n");
		return NULL;
	}

	SDL_DisplayMode display_mode;
	if (SDL_GetCurrentDisplayMode(0, &display_mode) != 0) {
		fprintf(stderr, "There was an error getting the current display information.\n");
		return NULL;
	}

	sdl_components->window = SDL_CreateWindow(
		"blue_hour",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		0
	);

	if (sdl_components->window == NULL) {
		fprintf(stderr, "There was an error creating the window.\n");
		return NULL;
	}

	sdl_components->renderer = SDL_CreateRenderer(sdl_components->window, -1, 0);

	if (sdl_components->renderer == NULL) {
		fprintf(stderr, "There was an error creating the renderer.\n");
		return NULL;
	}

	sdl_components->texture = SDL_CreateTexture(
		sdl_components->renderer,
		SDL_PIXELFORMAT_ABGR8888,
		SDL_TEXTUREACCESS_STREAMING,
		WINDOW_WIDTH,
		WINDOW_HEIGHT
	);

	if (sdl_components->texture == NULL) {
		fprintf(stderr, "There was an error creating the frame buffer texture.\n");
		return NULL;
	}

	return sdl_components;
}

void draw_grid() {
	for (size_t y = 0; y < WINDOW_HEIGHT; y += 10) {
		for (size_t x = 0; x < WINDOW_WIDTH; x += 10) {
			pixel_buffer[(WINDOW_WIDTH * y) + x] = 0xFF333333;
		}
	}
}

void draw_background() {
	for (size_t y = 0; y < WINDOW_HEIGHT; y++) {
		for (size_t x = 0; x < WINDOW_WIDTH; x++) {
			pixel_buffer[(WINDOW_WIDTH * y) + x] = 0xFF000000;
		}
	}
}

void render_loop(display_components_t* display)
{
	SDL_LockTexture(display->texture, NULL, (void**)&pixel_buffer, &display_pitch);

	draw_background();
	draw_grid();

	SDL_UnlockTexture(display->texture);
	SDL_RenderCopy(display->renderer, display->texture, NULL, NULL);
	SDL_RenderPresent(display->renderer);
}
