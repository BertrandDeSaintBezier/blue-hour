#include "update.h"

void update_loop(vertex_t* vertices, size_t count)
{
	for (size_t i = 0; i < count; i++)
	{
		vertex_t vertex = vertices[i];
		vertex.world_pos.x += 0.01;
		vertex.world_pos.y += 0.005;
		vertices[i] = vertex;
	}
}
