#ifndef SCENE_H
#define SCENE_H

#include "ecs/Entity.hpp"
#include <vector>

class Scene {
  public:
	std::vector<Entity *> entities;

	Entity *GetCamera();

	void Start();
	void Update();

	template <typename F, typename... Args>
	void CreateScene(F function, Args &&...args) {
		function(args...);
	}

};

#endif
