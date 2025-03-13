#ifndef CHUNK_RENDERER_H
#define CHUNK_RENDERER_H

#include "../engine/ecs/IComponent.hpp"
#include "../engine/utils/Model.hpp"
#include "Chunk.hpp"
#include "../entities/TileEntity.hpp"
#include "TileTexture.hpp"
#include "TileTransform.hpp"
#include <cstddef>
#include <unordered_map>
#include <vector>

struct ChunkRenderer : IComponent {
	ChunkModel *model;

	ChunkRenderer(ChunkModel *model) : model(model) {};

	void UpdateTile(int index, TileEntity *tile) {
		std::vector<unsigned int> vertices = TileToVertices(tile);
		for (size_t i = 0; i < vertices.size(); i++) {
			model->Set(tile->GetComponent<TileTexture>()->texture, index + i, vertices[0 + i]);
		}
	}

	void AddChunkToSSBO(Chunk chunk) {
		std::unordered_map<std::string, std::vector<TileEntity *>> textureSeperatedTiles;
		for (auto tile : chunk.tiles) {
			textureSeperatedTiles[tile->GetComponent<TileTexture>()->texture].push_back(tile);
		}
		for (auto pair : textureSeperatedTiles) {
			std::string textureName = pair.first;
			std::vector<TileEntity *> tiles = pair.second;

			std::vector<unsigned int> chunkVertices;
			for (auto tile : tiles) {
				for (auto vertex : TileToVertices(tile)) {
					chunkVertices.push_back(vertex);
				}
			}
			model->Fill(textureName, chunkVertices);
		}
	}

	std::vector<unsigned int> TileToVertices(TileEntity *tile) {
		TileTransform *transform = tile->GetComponent<TileTransform>();

		unsigned int vertex1 = (int(transform->position.x) & 0xFFFF) | (int(transform->position.y) << 16);
		unsigned int vertex2 = (int(transform->position.z) & 0xFFFF) | (int(transform->size.x) << 16) | (int(transform->size.y) << 24);
		return {vertex1, vertex2};
	}

	void Update() override {
		model->Render();
	}
};

#endif
