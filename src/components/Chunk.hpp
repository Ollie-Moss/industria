#ifndef CHUNK_H
#define CHUNK_H

#include "../engine/ecs/IComponent.hpp"
#include "Tile.hpp"

struct Chunk : IComponent {
	std::vector<Tile *> tiles;

	Chunk() {};
};

#endif
