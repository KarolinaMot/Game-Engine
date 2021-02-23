#pragma once
#include "Entity.h"
#include "Component.h"

class EntityManager
{
private:
	std::vector<Entity> entities;
public:
	void clearData();
	void update(float deltaTime);
	void render();
	bool hasNoEntities();
	Entity& addEntity(std::string entityName);
	std::vector<Entity*> getEntities() const;
	unsigned int getEntityCount();
};

