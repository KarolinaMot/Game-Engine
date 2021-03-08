#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <typeinfo>
#include "Constants.h"
#include "EntityManager.h"
#include "Component.h"

class EntityManager;
class Component;

class Entity {
private:
    EntityManager& manager;
    bool isActive;
    std::vector<Component*> components;
    std::map<const std::type_info*, Component*> componentTypeMap;

    public:
    std::string name;
    LayerType layer;
    Entity(EntityManager& manager);
    Entity(EntityManager& manager, std::string name, LayerType layer);
    void Update(float deltaTime);
    void Render();
    void Destroy();
    void ListAllComponents();
    bool IsActive() const;


    template <typename T, typename... TArgs> //template used to add components to an entity, so I don't have to create an add component method for each existing component
    T& AddComponent(TArgs&&... args) { //The capital T works as an Alias for the type of component that is being passed, Targs are the arguments being passed with the component
        T* newComponent(new T(std::forward<TArgs>(args)...)); //creates an object of the class Component
        newComponent->owner = this; //Sets the component's owner as the entity to which the  component is being added
        components.emplace_back(newComponent); //add components to the entity's component vector
        componentTypeMap[&typeid(*newComponent)] = newComponent; 
        newComponent->Initialize();
        return *newComponent; //return a pointer to the new component object
    }

    template <typename T>
    T* GetComponent() {
        return static_cast <T*>(componentTypeMap[&typeid(T)]);
    }

    template <typename T>
    bool HasComponents() const {
        return componentTypeMap.count(&typeid(T));
    }
};

#endif