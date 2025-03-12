#ifndef TILE_H
#define TILE_H

#include "../engine/ecs/Entity.hpp"
#include "TileTexture.hpp"
#include "TileTransform.hpp"

struct TileEntity : Entity {
	TileEntity(TileTexture *texture) {
		AddComponent(new TileTransform);
		AddComponent(texture);
	};
};

#endif
