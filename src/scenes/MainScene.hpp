#include "../engine/Scene.hpp"
#include "../engine/ecs/components/Camera.hpp"
#include "../components/Map.hpp"


struct MainScene : public Scene {
	MainScene() {
		ENTITY(map, new Map);
		ENTITY(cameraEntity, new Transform, new Camera);
	}
};
