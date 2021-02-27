#include <iostream>
#include "EntityManager.h"
#include "Entity.h"

void EntityManager::ClearData() {
    for (auto& entity : entities) {
        entity->Destroy();
    }
}

bool EntityManager::HasNoEntities() {
    return entities.size() == 0;
}

void EntityManager::Update(float deltaTime) {
    for (auto& entity : entities) {
        entity->Update(deltaTime);
    }
}

void EntityManager::Render() {
    for (auto& entity : entities) {
        entity->Render();
    }
}

void EntityManager::ListAllEntities() const{
    for (auto& entity : entities) {
        std::cout << "Entity name: "<<entity->name << std::endl;
        entity->ListAllComponents();
    }
}

Entity& EntityManager::AddEntity(std::string entityName) {//Creates entity and adds it to the entity manager
    Entity* entity = new Entity(*this, entityName); //creates entity
    entities.emplace_back(entity); //adds created entity to the entities vector
    return *entity; //returns entity
}

std::vector<Entity*> EntityManager::GetEntities() const {
    return entities;
}

unsigned int EntityManager::GetEntityCount() {
    return entities.size();
}
