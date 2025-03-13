#include "../engine/Scene.hpp"
#include "../engine/ecs/components/Renderer.hpp"
#include "../engine/ecs/components/Camera.hpp"
#include "../components/MapGenerator.hpp"
#include "../engine/Userinterface.hpp"
#include "../components/Map.hpp"
#include <vector>

// Main ENTITY macro
#define ENTITY(name, ...) \
    Entity* name = new Entity; \
    name->AddComponents({__VA_ARGS__}); \
    entities.push_back(name);

struct MainScene : public Scene {
	MainScene() {
		CreateScene([&]() {

			ENTITY(map, new Map);

			ENTITY(cameraEntity, new Transform, new Camera);
		});
	}
};
