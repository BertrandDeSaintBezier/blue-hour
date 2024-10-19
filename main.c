#include<stdio.h>
#include<stdbool.h>

#include "controls.h"
#include "update.h"
#include "display.h"

int main(int argc, char* args[]) {
	display_components_t display;
	display_components_t* result = setup_sdl_components(&display);
	if (result == NULL) {
		return 1;
	}

	display = *result;
	printf("Display components initialized.\n");

	bool running = true;

	vertex_t vertices[3 * 3 * 3];
	for (size_t z = 0; z < 3; z++) {
		for (size_t y = 0; y < 3; y++) {
			for (size_t x = 0; x < 3; x++) {
				vertex_t temp = {
					.world_pos = {.x = x, .y = y, .z = z + 1},
					.world_rot = {.x = 0, .y = 0, .z = 0}
				};
				vertices[3 * 3 * z + 3 * y + x] = temp;
			}
		}
	}

	pointcloud_t cube = { .vertices = &vertices, .count = 3 * 3 * 3 };

	while (running) {
		running = process_player_input();

		update_loop(cube.vertices, cube.count);

		render_loop(&display, cube.vertices, cube.count);
	}

	cleanup_sdl_components(&display);
	return 0;
}