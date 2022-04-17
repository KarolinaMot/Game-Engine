#pragma once

#include <SDL2/SDL.h>
#include "Engine.h"
#include "EntityManager.h"
#include "TransformComponent.h"

class ColliderComponent : public Component {
public:
    std::string colliderTag;
    SDL_Rect collider;
    SDL_Rect sourceRectangle;
    SDL_Rect destinationRectangle;
    TransformComponent* transform;


    ColliderComponent(std::string colliderTag, int x, int y, int width, int height) {
        this->colliderTag = colliderTag;
        this->collider = { x, y, width, height };
    }

    void Initialize() override {
        if (owner->HasComponent<TransformComponent>()) {
            transform = owner->GetComponent<TransformComponent>();
            sourceRectangle = { 0, 0, transform->width, transform->height };
            destinationRectangle = { collider.x, collider.y, collider.w, collider.h };
        }
    }

    void Update(float deltaTime) override {
        collider.x = static_cast<int>(transform->position.x); //sets collider.x to the x position of the passed transform
        collider.y = static_cast<int>(transform->position.y); //sets collider.y to the y position of the passed transform
        collider.w = transform->width * transform->scale;
        collider.h = transform->height * transform->scale;
        destinationRectangle.x = collider.x - Engine::camera.x;
        destinationRectangle.y = collider.y - Engine::camera.y;
    }

    void RenderIf(bool debug) override{
        if (debug)
        {
            SDL_RenderDrawRect(Engine::renderer, &destinationRectangle);     
        }
           
    }
};

