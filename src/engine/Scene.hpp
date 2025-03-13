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
};

#endif
