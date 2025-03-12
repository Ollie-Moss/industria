#ifndef MAP_H
#define MAP_H

#include "../engine/ecs/IComponent.hpp"
#include "Chunk.hpp"
#include "ChunkEntity.hpp"
#include "MapGenerator.hpp"

struct Map : IComponent {
	std::vector<ChunkEntity*> chunks;

	Map() {};

	void Start() override {
	}

	void Update() override {
        for(auto chunk : chunks){
            chunk->UpdateComponents();
        }
	};
};

#endif
