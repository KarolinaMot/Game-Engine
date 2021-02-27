#include "Entity.h"

Entity::Entity(EntityManager& manager) : manager(manager) {
    this->isActive = true;
}

Entity::Entity(EntityManager& manager, std::string name) : manager(manager), name(name) { //Activates entity
    this->isActive = true;
}

void Entity::Update(float deltaTime) {
    for (auto& component : components) {
        component->Update(deltaTime);
    }
}

void Entity::Render() {
    for (auto& component : components) {
        component->Render();
    }
}

void Entity::Destroy() {
    this->isActive = false;
}

void Entity::ListAllComponents(){
    for (auto& mapElement : componentTypeMap)
    {
        std::cout << "     Component: " << mapElement.first->name() << std::endl;
    }
}

bool Entity::IsActive() const {
    return this->isActive;
}
