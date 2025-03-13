#ifndef TILE_TRANSFORM_H
#define TILE_TRANSFORM_H

#include "../engine/ecs/IComponent.hpp"
#include <glm/ext/vector_int2.hpp>
#include <glm/ext/vector_int3.hpp>

struct TileTransform : IComponent {
	glm::ivec3 position = glm::ivec3(0, 0, 0);
	glm::ivec2 size = glm::ivec2(1, 1);

	TileTransform() {};
	TileTransform(glm::ivec3 position) : position(position) {};
};

#endif
