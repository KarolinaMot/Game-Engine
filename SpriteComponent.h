#pragma once
#include "SDL.h"
#include "ECS.h"
#include "PositionComponent.h"
#include "TextureManager.h"

class SpriteComponent : public Component
{
	private:
		PositionComponent* position;
		SDL_Texture* texture;
		SDL_Rect srcRect, destRect;

	public:
		SpriteComponent() = default;
		SpriteComponent(const char* path){
			setTex(path);
		}

		void setTex(const char* path) { //Funkcija kuri bus naudojama norit pakeisti objekto vaizda, pvz kai akmuo sudauzomas
			texture = TextureManager::LoadTexture(path);
		}
		void init() override{
			position = &entity->getComponent<PositionComponent>();
			srcRect.x = srcRect.y = 0;
			srcRect.w = 50;
			srcRect.h = 37;
			destRect.w =  108;
			destRect.h =  80;
		}

		void update() override{
			destRect.x = position->x();
			destRect.y = position->y();
		}

		void draw() override {
			TextureManager::Draw(texture, srcRect, destRect);
		}
};

