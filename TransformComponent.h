#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H
#include "EntityManager.h"
#include "glm/glm.hpp"
#include <SDL2/SDL.h>
#include "Engine.h"

class TransformComponent : public Component {
public:
    glm::vec2 position;
    glm::vec2 velocity;
    int width;
    int height;
    int scale;
   

    TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s) { //Transform component's constructor, which sets the entity's starting position, velocity, height, width and scale
        position = glm::vec2(posX, posY); //sets the entity's starting position
        velocity = glm::vec2(velX, velY); //sets the entity's velocity
        width = w; //entity's width
        height = h; //entity's height
        scale = s; //entity's scale
    }

    void Initialize() override {

    }

    void Update(float deltaTime) override {
        position.x += velocity.x * deltaTime;
        position.y += velocity.y * deltaTime;
    }

    void Render() override {
    }
};

#endif
