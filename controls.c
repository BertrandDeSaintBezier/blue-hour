#include "controls.h"

bool process_player_input()
{
	SDL_Event event_buff;
	SDL_PollEvent(&event_buff);

	switch (event_buff.type)
	{
	case SDL_QUIT:
		return false;
	case SDL_KEYDOWN:
		if (event_buff.key.keysym.sym == SDLK_ESCAPE) {
			return false;
		}
		break;
	default:
		break;
	}
	return true;
}
