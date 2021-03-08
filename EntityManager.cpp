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
   /* for (auto& entity : entities) {
        entity->Render();
    }*/

    for (int layerNumber = 0; layerNumber < NUM_LAYERS; layerNumber++){
        for (auto& entity : GetEntitiesByLayer(static_cast<LayerType>(layerNumber)))
        {
            entity->Render();
        }
    }
}

void EntityManager::ListAllEntities() const{
    for (auto& entity : entities) {
        std::cout << "Entity name: "<<entity->name << std::endl;
        entity->ListAllComponents();
    }
}

Entity& EntityManager::AddEntity(std::string entityName, LayerType layer) {//Creates entity and adds it to the entity manager
    Entity* entity = new Entity(*this, entityName, layer); //creates entity
    entities.emplace_back(entity); //adds created entity to the entities vector
    return *entity; //returns entity
}

std::vector<Entity*> EntityManager::GetEntities() const {
    return entities;
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType layer) const
{
    std::vector<Entity*> selectedEntities;
    for (auto& entity : entities) {
        if (entity->layer == layer)
        {
            selectedEntities.emplace_back(entity);
        } 
    }
    return selectedEntities;
}

unsigned int EntityManager::GetEntityCount() {
    return entities.size();
}
