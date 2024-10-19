#include "vertex.h"
#include "display.h"

void project_vertex(vertex_t* vertex)
{
	vec2_t projected_pos = 
	{
		.x = (vertex->world_pos.x / vertex->world_pos.z),
		.y = (vertex->world_pos.y / vertex->world_pos.z)
	};
	vertex->projected_pos = projected_pos;

	vertex->projected_pos.x += WINDOW_WIDTH / 2;
	vertex->projected_pos.y += WINDOW_HEIGHT / 2;
}