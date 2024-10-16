#include<stdio.h>
#include<stdbool.h>

#include "controls.h"
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
	while (running) {
		running = process_player_input();
		
		 // update();

		render_loop(&display);
	}
}