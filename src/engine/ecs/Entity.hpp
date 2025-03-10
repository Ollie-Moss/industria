#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include "IComponent.hpp"

class Entity {
  public:
	int ID;

	std::vector<IComponent *> Components;

	void AddComponent(IComponent *component);

	template <typename T>
	IComponent *GetComponent();

	void UpdateComponents();
};

#endif
