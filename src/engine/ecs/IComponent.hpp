#ifndef ICOMPONENT_H
#define ICOMPONENT_H

class Entity;

class IComponent {
  public:
	Entity *entity = nullptr;

	virtual void Update() {};
};

#endif
