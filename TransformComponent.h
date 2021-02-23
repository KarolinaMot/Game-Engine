#pragma once
#include "EntityManager.h"
#include "Engine.h"
#include <SDL2/SDL.h>
#include <glm/glm.hpp>


class TransformComponent {
	public:
		glm::vec2 position;
		glm::vec2 velocity;
		int width;
		int height;
		int scale;

		TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s) {
			position = glm::vec2(posX, posY);
			velocity = glm::vec2(velX, velY);
			width = w;
			height = h;
			scale = s;
		}

		void initialize() override {}

		void update(float delta_time) override {
			position.x += velocity.x * delta_time;
			position.y += velocity.y * delta_time;
		}

		void render() override {
			SDL_Rect transform_rectangle = { (int)position.x, (int)position.y, width, height };
			SDL_SetRenderDrawColor(Engine::renderer, 0, 0, 0, 255);
			SDL_RenderFillRect(Engine::renderer, &transform_rectangle);
		}
};