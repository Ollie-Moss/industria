#include "ResourceManager.hpp"
#include "utils/Shader.hpp"
#include "utils/Texture.hpp"
#include <map>
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

// Instantiate static variables
std::map<std::string, Texture2D> ResourceManager::Textures;
std::map<std::string, Shader> ResourceManager::Shaders;

Shader ResourceManager::LoadShader(const char *vShaderFile,
								   const char *fShaderFile, std::string name) {
	Shader shader;
	shader.Compile(vShaderFile, fShaderFile);
	Shaders[name] = shader;
	return Shaders[name];
}
void ResourceManager::Init() {
	stbi_set_flip_vertically_on_load(true);

	LoadShader("src/engine/utils/shaders/vSpriteShader.glsl",
			   "src/engine/utils/shaders/fSpriteShader.glsl",
			   "SpriteShader");

	LoadShader("src/engine/utils/shaders/vLineShader.glsl",
			   "src/engine/utils/shaders/fLineShader.glsl", "LineShader");

	LoadShader("src/engine/utils/shaders/vTextShader.glsl",
			   "src/engine/utils/shaders/fTextShader.glsl", "TextShader");

	LoadShader("src/engine/utils/shaders/vQuadShader.glsl",
			   "src/engine/utils/shaders/fQuadShader.glsl", "QuadShader");

    // Buildings
	ResourceManager::LoadTexture("CONVEYOR_STRAIGHT", 1.0f, "sprites/conveyors/conveyor_straight_up.png");
	ResourceManager::LoadTexture("FURNACE_SMALL", 1.0f, "sprites/buildings/furnace.png");
	ResourceManager::LoadTexture("FURNACE", 1.0f, "sprites/buildings/furnace_large.png");
	ResourceManager::LoadTexture("INSERTER", 1.0f, "sprites/buildings/inserter.png");

    // UI
	ResourceManager::LoadTexture("INVENTORY_BACKGROUND", 1.0f, "sprites/UI/inventory_background.png");
	ResourceManager::LoadTexture("INVENTORY_SLOT", 1.0f, "sprites/UI/inventory_slot.png");
	ResourceManager::LoadTexture("TILE_SELCTOR", 1.0f, "sprites/UI/tile_selector.png");

    // Items
	ResourceManager::LoadTexture("IRON_ORE_ITEM", 1.0f, "sprites/items/iron_ore.png");
	ResourceManager::LoadTexture("COPPER_ORE_ITEM", 1.0f, "sprites/items/copper_ore.png");
	ResourceManager::LoadTexture("COAL_ITEM", 1.0f, "sprites/items/coal.png");
	ResourceManager::LoadTexture("LEAVES_ITEM", 1.0f, "sprites/items/leaves.png");
	ResourceManager::LoadTexture("IRON_PLATE_ITEM", 1.0f, "sprites/items/iron_plate.png");
	ResourceManager::LoadTexture("COPPER_PLATE_ITEM", 1.0f, "sprites/items/copper_plate.png");
	ResourceManager::LoadTexture("GEARS_ITEM", 1.0f, "sprites/items/gears.png");
	ResourceManager::LoadTexture("WIRE_ITEM", 1.0f, "sprites/items/wire.png");
	ResourceManager::LoadTexture("CIRCUIT_BOARDS_ITEM", 1.0f, "sprites/items/circuit_board.png");

    // Environment
	ResourceManager::LoadTexture("TREE", 1.0f, "sprites/environment/tree.png");
	ResourceManager::LoadTexture("TILE_SELCTOR", 1.0f, "sprites/environment/grass.png");

    // Tiles
	ResourceManager::LoadTexture("GRASS_TILE_1", 1.0f, "sprites/tiles/grass_tile_1.png");
	ResourceManager::LoadTexture("GRASS_TILE_2", 1.0f, "sprites/tiles/grass_tile_2.png");
};

Shader ResourceManager::GetShader(std::string name) {
	return Shaders[name];
}

Texture2D ResourceManager::LoadTexture(std::string name, bool alpha,
									   const char *file) {
	// create texture object
	Texture2D texture = Texture2D();
	if (alpha) {
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
	}

	// load image
	int width, height, nrChannels;
	unsigned char *data = stbi_load(file, &width, &height, &nrChannels, STBI_rgb_alpha);
	// now generate texture
	texture.Generate(width, height, data);
	// and finally free image data
	stbi_image_free(data);
	Textures[name] = texture;
	return Textures[name];
}

Texture2D ResourceManager::GetTexture(std::string name) {
	return Textures[name];
}

void ResourceManager::Clear() {
	// (properly) delete all shaders
	for (auto iter : Shaders)
		glDeleteProgram(iter.second.ID);
	// (properly) delete all textures
	for (auto iter : Textures)
		glDeleteTextures(1, &iter.second.ID);
}
