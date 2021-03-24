#pragma once

#include "Entity.h"
#include "Component.h"
#include <vector>

class EntityManager {
private:
    std::vector<Entity*> entities;
public:
    void ClearData();
    void Update(float deltaTime);
    void DestroyInactiveEntities();
    void Render();
    void Render(bool isRendering);
    bool HasNoEntities() const;
    unsigned int GetEntityCount() const;
    void ListAllEntities() const;
    void DebugMode();
    std::vector<Entity*> GetEntities() const;
    std::vector<Entity*> GetEntitiesByLayer(LayerType layer) const;
    Entity& AddEntity(std::string entityName, LayerType layer);
    CollisionType CheckCollisions() const;
};


