#ifndef ENTITY_H
#define ENTITY_H

#include "IComponent.hpp"
#include <vector>

class Entity {
  public:
	int ID;

	std::vector<IComponent *> Components;

	void AddComponent(IComponent *component) {
		Components.push_back(component);
	};

	void UpdateComponents() {
		for (int i = 0; i < Components.size(); i++) {
			IComponent *component = Components[i];
			component->Update();
		}
	};
};

#endif
