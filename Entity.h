#pragma once
#include <vector>
#include<string>
#include "EntityManager.h"
#include "Component.h"


class Entity{
	private:
		EntityManager& manager;
		bool is_active;
		std::vector<Component*> components;
	public:
		std::string name;
		Entity(EntityManager& manager);
		Entity(EntityManager& manager, std::string name);
		void update(float deltaTime);
		void render();
		void destroy();
		bool isActive() const;

};

