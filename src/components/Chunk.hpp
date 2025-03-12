#ifndef CHUNK_H
#define CHUNK_H

#include "../engine/ecs/IComponent.hpp"
#include "../engine/ecs/components/Transform.hpp"
#include "TileEntity.hpp"

struct ChunkRenderer;

struct Chunk : IComponent {
	std::vector<TileEntity *> tiles;
	Transform *transform;
	ChunkRenderer *renderer;

	Chunk(ChunkRenderer *renderer, Transform *transform) : renderer(renderer),
														   transform(transform) {};

	void Update() override {
		for (auto tile : tiles) {
			tile->UpdateComponents();
		}
	}
};


#endif
