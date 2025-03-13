#ifndef TILE_H
#define TILE_H

#include "../engine/ecs/Entity.hpp"
#include "../components/TileTexture.hpp"
#include "../components/TileTransform.hpp"

struct TileEntity : Entity {
	TileEntity(TileTexture *texture) {
		AddComponent(new TileTransform);
		AddComponent(texture);
	};
};

#endif
