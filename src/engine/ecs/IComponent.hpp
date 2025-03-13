#ifndef ICOMPONENT_H
#define ICOMPONENT_H

class Entity;

#define COMPONENT(component) AddComponent(new component)

class IComponent {
  public:
	Entity *entity = nullptr;

	virtual void Start() {};
	virtual void Update() {};
};

#endif
