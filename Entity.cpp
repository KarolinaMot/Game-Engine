#include "Entity.h"

Entity::Entity(EntityManager& manager):manager(manager){
	this->is_active = true;
}

Entity::Entity(EntityManager& manager, std::string name):manager(manager), name(name){
	this->is_active = true;
}

void Entity::update(float deltaTime){
	for (auto* component : components) {
		component->update(deltaTime);
	}
}

void Entity::render(){
	for (auto& component : components)
		component->render();
}

void Entity::destroy(){
	this->is_active = false;
}

bool Entity::isActive() const{
	return this->is_active;
}
