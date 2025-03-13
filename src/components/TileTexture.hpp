#ifndef TILE_TEXTURE_H
#define TILE_TEXTURE_H

#include "../engine/ecs/IComponent.hpp"
#include <string>

struct TileTexture : IComponent {
	std::string texture = "";
	TileTexture() {};
	TileTexture(std::string texture) : texture(texture) {};
};

#endif
