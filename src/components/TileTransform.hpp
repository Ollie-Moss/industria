#ifndef TILE_TRANSFORM_H
#define TILE_TRANSFORM_H

#include "../engine/ecs/IComponent.hpp"
#include <glm/ext/vector_int2.hpp>

struct TileTransform : IComponent {
	glm::ivec2 position = glm::ivec2(0, 0);
	glm::ivec2 size = glm::ivec2(0, 0);
};

#endif
