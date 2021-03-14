#include <iostream>
#include "EntityManager.h"
#include "Collision.h"
#include "ColliderComponent.h"

void EntityManager::ClearData() {
    for (auto& entity : entities) {
        entity->Destroy();
    }
}

void EntityManager::Update(float deltaTime) {
    for (auto& entity : entities) {
        entity->Update(deltaTime);
    }
}

void EntityManager::Render() {
    for (int layerNumber = 0; layerNumber < NUM_LAYERS; layerNumber++) {
        for (auto& entity : GetEntitiesByLayer(static_cast<LayerType>(layerNumber))) {
            entity->Render();
        }
    }
}

void EntityManager::Render(bool isRendering) {
    for (int layerNumber = 0; layerNumber < NUM_LAYERS; layerNumber++) {
        for (auto& entity : GetEntitiesByLayer(static_cast<LayerType>(layerNumber))) {
            entity->Render(isRendering);
        }
    }
}

bool EntityManager::HasNoEntities() const {
    return entities.size() == 0;
}

unsigned int EntityManager::GetEntityCount() const {
    return entities.size();
}

std::vector<Entity*> EntityManager::GetEntities() const {
    return entities;
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType layer) const {
    std::vector<Entity*> selectedEntities;
    for (auto& entity : entities) {
        if (entity->layer == layer) {
            selectedEntities.emplace_back(entity);
        }
    }
    return selectedEntities;
}

void EntityManager::ListAllEntities() const {
    unsigned int i = 0;
    for (auto& entity : entities) {
        std::cout << "Entity[" << i << "]: " << entity->name << std::endl;
        entity->ListAllComponents();
        i++;
    }
}

void EntityManager::DebugMode()
{
    for (auto& entity : entities) {
        if (entity->HasComponent<ColliderComponent>())
        {
            ColliderComponent* collider = entity->GetComponent<ColliderComponent>();
            SDL_RenderDrawRect(Engine::renderer, &collider->destinationRectangle);
            std::cout << collider->colliderTag << "(" << collider->destinationRectangle.x << "; " << collider->destinationRectangle.y << "); " << entity->layer << std::endl << std::endl;
        }
    }
}

CollisionType EntityManager::CheckCollisions() const {
    for (int i = 0; i < entities.size() - 1; i++) {//looping through all entities
        auto& thisEntity = entities[i]; //the entity getting checked
        if (thisEntity->HasComponent<ColliderComponent>()) { //checking if entity has a collider component
            ColliderComponent* thisCollider = thisEntity->GetComponent<ColliderComponent>(); //the entity's component
            for (int j = i + 1; j < entities.size(); j++) { //loops again through all entities again
                auto& thatEntity = entities[j]; //an entity that is maybe colliding with "thisEntity"
                if (thisEntity->name.compare(thatEntity->name) != 0 && thatEntity->HasComponent<ColliderComponent>()) { //checking for a collider component and that both entity's names are different
                    ColliderComponent* thatCollider = thatEntity->GetComponent<ColliderComponent>(); //the collider of that second entity
                    if (Collision::CheckRectangleCollision(thisCollider->collider, thatCollider->collider)) { //checks collision between both entities
                        if (thisCollider->colliderTag.compare("PLAYER") == 0 && thatCollider->colliderTag.compare("ENEMY") == 0) { //checks what type of collision happened
                            return PLAYER_ENEMY_COLLISION;
                        }
                        if (thisCollider->colliderTag.compare("PLAYER") == 0 && thatCollider->colliderTag.compare("PROJECTILE") == 0) {
                            return PLAYER_PROJECTILE_COLLISION;
                        }
                        if (thisCollider->colliderTag.compare("ENEMY") == 0 && thatCollider->colliderTag.compare("FRIENDLY_PROJECTILE") == 0) {
                            return ENEMY_PROJECTILE_COLLISION;
                        }
                        if (thisCollider->colliderTag.compare("PLAYER") == 0 && thatCollider->colliderTag.compare("LEVEL_COMPLETE") == 0) {
                            return PLAYER_LEVEL_COMPLETE_COLLISION;
                        }
                    }
                }
            }
        }
    }
    return NO_COLLISION; //if there is no collision, returns no collision
}

Entity& EntityManager::AddEntity(std::string entityName, LayerType layer) {
    Entity* entity = new Entity(*this, entityName, layer);
    entities.emplace_back(entity);
    return *entity;
}
