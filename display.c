#include "display.h"

size_t display_pitch;
uint32_t* pixel_buffer = NULL;

display_components_t* setup_sdl_components(display_components_t* display) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "There was an error initializing SDL.\n");
		return NULL;
	}

	SDL_DisplayMode display_mode;
	if (SDL_GetCurrentDisplayMode(0, &display_mode) != 0) {
		fprintf(stderr, "There was an error getting the current display information.\n");
		return NULL;
	}

	display->window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_BORDERLESS
	);

	if (display->window == NULL) {
		fprintf(stderr, "There was an error creating the window.\n");
		return NULL;
	}

	display->renderer = SDL_CreateRenderer(display->window, -1, 0);

	if (display->renderer == NULL) {
		fprintf(stderr, "There was an error creating the renderer.\n");
		return NULL;
	}

	display->texture = SDL_CreateTexture(
		display->renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		WINDOW_WIDTH,
		WINDOW_HEIGHT
	);

	if (display->texture == NULL) {
		fprintf(stderr, "There was an error creating the frame buffer texture.\n");
		return NULL;
	}

	return display;
}

void draw_grid() {
	for (size_t y = 0; y < WINDOW_HEIGHT; y += 10) {
		for (size_t x = 0; x < WINDOW_WIDTH; x += 10) {
			pixel_buffer[(WINDOW_WIDTH * y) + x] = 0xFF333333;
		}
	}
}

void draw_background() {
	for (size_t i = 0; i < WINDOW_WIDTH * WINDOW_HEIGHT; i++) {
		pixel_buffer[i] = 0xFF000000;
	}
}

void draw_vertex(vertex_t* vertices, size_t count) {
	for (size_t i = 0; i < count; i++) {
		vertex_t vertex = vertices[i];
		project_vertex(&vertex);
		float vertex_area = 4.0f;// / (vertex.world_pos.z <= 0 ? 1 : vertex.world_pos.z);
		for (size_t y = vertex.projected_pos.y; y < vertex.projected_pos.y + vertex_area; y++) {
			for (size_t x = vertex.projected_pos.x; x < vertex.projected_pos.x + vertex_area; x++) {
				pixel_buffer[(WINDOW_WIDTH * y) + x] = 0xFFFF0000;
			}
		}
	}
}

void render_loop(display_components_t* display, vertex_t* vertices, size_t count) {
	SDL_LockTexture(display->texture, NULL, (void**)&pixel_buffer, &display_pitch);

	draw_background();
	draw_grid();
	draw_vertex(vertices, count);

	SDL_UnlockTexture(display->texture);
	SDL_RenderCopy(display->renderer, display->texture, NULL, NULL);
	SDL_RenderPresent(display->renderer);
}

void cleanup_sdl_components(display_components_t* display) {
	SDL_DestroyWindow(display->window);
	SDL_DestroyTexture(display->texture);
	SDL_DestroyRenderer(display->texture);
}
