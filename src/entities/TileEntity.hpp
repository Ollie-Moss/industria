#ifndef TILE_H
#define TILE_H

#include "../engine/ecs/Entity.hpp"
#include "../components/TileTexture.hpp"
#include "../components/TileTransform.hpp"
#include <glm/ext/vector_int3.hpp>
#include <string>

struct TileEntity : Entity {
	TileEntity(glm::ivec3 position, std::string texture) {
		COMPONENT(TileTransform(position));
		COMPONENT(TileTexture(texture));
	};
};

#endif
