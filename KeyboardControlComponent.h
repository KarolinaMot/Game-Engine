#pragma once
#include "Engine.h"
#include <SDL2/SDL.h>
#include <string>
#include "EntityManager.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "Constants.h"

class KeyboardControlComponent : public Component{
	public: 
		std::string upKey = "1073741906";
		std::string downKey = "1073741905";
		std::string rightKey = "1073741903";
		std::string leftKey = "1073741904";
		std::string attackKey = std::to_string(SDL_BUTTON_LEFT);
		TransformComponent* transform;
		SpriteComponent* sprite;
		int speed;
		bool movesUp, movesDown, movesRight, movesLeft;

		KeyboardControlComponent(int speed, bool movesUp, bool movesDown, bool movesRight, bool movesLeft) {

			this->speed = speed;
			this->movesUp = movesUp;
			this->movesDown = movesDown;
			this->movesRight = movesRight;
			this->movesLeft = movesLeft;
		}

		void Initialize() override {
			transform = owner->GetComponent<TransformComponent>();
			sprite = owner->GetComponent<SpriteComponent>();
		}

		void Update(float deltaTime) override {
			if (Engine::event.type == SDL_KEYDOWN) {
				std::string keyCode = std::to_string(Engine::event.key.keysym.sym); 
				if (keyCode.compare(upKey) == 0) {
					if(this->movesUp && transform->position.y - speed >=0){
						transform->velocity.y = -speed;
						transform->velocity.x = 0;
					}
					if (transform->position.y < 0) transform->position.y = 0;
				}
				if (keyCode.compare(rightKey) == 0 && this->movesRight ){
					if(transform->position.x + speed <= WINDOW_WIDTH)
					{ transform->velocity.y = 0;
					transform->velocity.x = speed;}					
					if (transform->position.x > WINDOW_WIDTH - transform->width) transform->position.x = WINDOW_WIDTH - transform->width;
					if (sprite->hasDirection) sprite->Play("RightAnimation");
				}
				if(keyCode.compare(downKey)==0 && this->movesDown){
					if(transform->position.y + speed <= WINDOW_HEIGHT){
					transform->velocity.y = speed;
					transform->velocity.x = 0;}
					if (transform->position.y > WINDOW_HEIGHT) transform->position.y = WINDOW_HEIGHT;
				}
				if(keyCode.compare(leftKey) ==0 && this->movesLeft ){
					if (transform->position.x - speed >= 0) {
						transform->velocity.y = 0;
						transform->velocity.x = -speed;
					}
					if (transform->position.x < 0) transform->position.x = 0;
					if (sprite->hasDirection)  sprite->Play("LeftAnimation");
				}
				if(keyCode.compare(attackKey) == 0){}
			}
			if (Engine::event.type == SDL_KEYUP) {
				std::string keyCode = std::to_string(Engine::event.key.keysym.sym);
				if (keyCode.compare(upKey) == 0) { transform->velocity.y = 0; }
				if (keyCode.compare(rightKey) == 0) { transform->velocity.x = 0; }
				if (keyCode.compare(downKey) == 0) { transform->velocity.y = 0; }
				if (keyCode.compare(leftKey) == 0) { transform->velocity.x = 0; }
				if (keyCode.compare(attackKey) == 0) {}
			}

		}
		
};

