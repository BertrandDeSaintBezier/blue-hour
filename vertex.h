#pragma once
#include<stdio.h>

#include "vector.h"

typedef struct {
	vec3_t world_pos;
	vec3_t world_rot;
	vec2_t projected_pos;
} vertex_t;

typedef struct {
	vertex_t* vertices;
	size_t count;
}pointcloud_t;

extern void project_vertex(vertex_t* vertex);