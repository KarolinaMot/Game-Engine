#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include "Component.h"
#include <vector>
#include <string>


class EntityManager{
private:
    std::vector<Entity*> entities;
public:
    void ClearData();
    void Update(float deltaTime);
    void Render();
    void ListAllEntities() const;
    bool HasNoEntities();
    Entity& AddEntity(std::string entityName);
    std::vector<Entity*> GetEntities() const;
    unsigned int GetEntityCount();
};

#endif
