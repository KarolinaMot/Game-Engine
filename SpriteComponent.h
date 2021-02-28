#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

	#include <SDL2/SDL.h>
	#include "TextureManager.h"
	#include "AssetManager.h"
	#include "Animation.h"

class SpriteComponent : public Component {
	private:
		TransformComponent* transform;
		SDL_Texture* texture;
		SDL_Rect sourceRectangle;
		SDL_Rect destinationRectangle;
		bool isAnimated;
		int numFrames;
		int animationSpeed;
		bool isFixed;
		std::map<std::string, Animation> animations;
		std::string currentAnimationName;
		unsigned int animationIndex = 0;

	public:
		SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
		bool hasDirection;

		SpriteComponent(std::string assetTextureId, bool isFixed) { //if animation parameters aren't  passed, then entity isn't animated
			this->isAnimated = false;
			this->isFixed = isFixed;
			SetTexture(assetTextureId);
		}

		SpriteComponent(std::string id, int numFrames, int animationSpeed, bool hasDirection, bool isFixed){ //Sprite component constructor which sets that the component is animated, its frame number, animation speed, fixation and directions
			isAnimated = true;
			this->numFrames = numFrames;
			this->animationSpeed = animationSpeed;
			this->isFixed = isFixed;
			this->hasDirection = hasDirection;

			if(hasDirection){ //if entity has direction, flips the animation for diferent directions
				Animation rightAnimation = Animation(0, numFrames, animationSpeed);//animation for flipping right
				Animation leftAnimation = Animation(1, numFrames, animationSpeed);//animation for flipping left

				animations.emplace("RightAnimation", rightAnimation);//adds the animations to the animation map
				animations.emplace("LeftAnimation", leftAnimation);//adds the animations to the animation map

				this->animationIndex = 0;
				this->currentAnimationName = "RightAnimation";
			}
			else { //if entity doesnt have directions, sets a single animation 
				Animation singleAnimation = Animation(0, numFrames, animationSpeed);
				animations.emplace("SingleAnimation", singleAnimation);
				this->animationIndex = 0;
				this->currentAnimationName = "SingleAnimation";
			}
			Play(this->currentAnimationName);
			SetTexture(id);

		}

		void Play(std::string animationName) { //plays the animation 
			numFrames = animations[animationName].numFrames; //sets the animation's number of frames
			animationIndex = animations[animationName].index; //sets the animation index
			animationSpeed = animations[animationName].animationSpeed; //sets the animation speed
			currentAnimationName = animationName; //sets animation name
		}

		void SetTexture(std::string assetTextureId) { //sets entity's sprite image
			texture = Engine::assetManager->GetTexture(assetTextureId);
		}

		void Initialize() override {
			transform = owner->GetComponent<TransformComponent>();
			sourceRectangle.x = 0;
			sourceRectangle.y = 0;
			sourceRectangle.w = transform->width;
			sourceRectangle.h = transform->height;
		}

		void Update(float deltaTime) override {
			if (isAnimated) {
				sourceRectangle.x = sourceRectangle.w * static_cast<int>((SDL_GetTicks() / animationSpeed) % numFrames); //slides source rectangle to the right with every frame to change picture
			}
			sourceRectangle.y = animationIndex * transform->height;

			destinationRectangle.x = static_cast<int>(transform->position.x);
			destinationRectangle.y = static_cast<int>(transform->position.y);
			destinationRectangle.w = transform->width * transform->scale;
			destinationRectangle.h = transform->height * transform->scale;
		}

		void Render() override {
			TextureManager::Draw(texture, sourceRectangle, destinationRectangle, spriteFlip);
		}
};

#endif
