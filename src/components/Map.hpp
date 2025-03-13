#ifndef MAP_H
#define MAP_H

#include "../engine/ecs/IComponent.hpp"
#include "../entities/ChunkEntity.hpp"
#include "Chunk.hpp"
#include "MapGenerator.hpp"
#include "../engine/Simplex.hpp"
#include "../engine/ecs/components/Camera.hpp"
#include <glm/ext/vector_float2.hpp>
#include <unordered_map>
#include <utility>

namespace std {
template <>
struct hash<glm::ivec2> {
	size_t operator()(const glm::ivec2 &v) const {
		// Hash each component (x, y) of the ivec2
		size_t h1 = hash<int>()(v.x);
		size_t h2 = hash<int>()(v.y);

		// Combine the hashes of x and y components
		size_t combined = h1;
		combined ^= h2 + 0x9e3779b9 + (combined << 6) + (combined >> 2); // Mixing h2 into h1

		return combined;
	};
};
} // namespace std

struct Map : IComponent {
	std::unordered_map<glm::ivec2, ChunkEntity *> chunks;

	Map() {};

	void Start() override {
	}

	void Update() override {
		std::pair<glm::ivec2, glm::ivec2> chunkCoords = Simplex::view.Camera->GetComponent<Camera>()->GetChunkPositionsInView();
		for (int y = chunkCoords.first.y; y < chunkCoords.second.y; y++) {
			for (int x = chunkCoords.first.x; x < chunkCoords.second.x; x++) {
				glm::ivec2 chunkCoord = glm::ivec2(x, y);
				if (chunks[chunkCoord] == nullptr) {
					ChunkEntity *chunk = new ChunkEntity(chunkCoord);
					chunks[chunkCoord] = chunk;
					chunk->GetComponent<Chunk>()->Generate();
				}
			}
		} // Remove chunks outside the range
		for (auto it = chunks.begin(); it != chunks.end();) {
			glm::ivec2 chunkCoord = it->first;

			// Check if the chunk is outside the range
			if (chunkCoord.x < chunkCoords.first.x - 10 || chunkCoord.x >= chunkCoords.second.x + 10 ||
				chunkCoord.y < chunkCoords.first.y - 10 || chunkCoord.y >= chunkCoords.second.y + 10) {

				// If outside the range, remove the chunk
				delete it->second;	   // Free the memory if necessary
				it = chunks.erase(it); // Remove the chunk from the map and get the next iterator
			} else {
				++it; // Continue with the next chunk if it's within the range
			}
		}
		for (auto chunk : chunks) {
			chunk.second->UpdateComponents();
		}
	};
};

#endif
