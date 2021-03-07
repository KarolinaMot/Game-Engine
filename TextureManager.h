#pragma once
#include <SDL2/SDL_image.h>
#include <string>
#include <map>
#include "Engine.h"

class TextureManager
{
	public:
		static SDL_Texture* LoadTexture(const char* filename); //funkcija kuri uzkraus tekstura
		static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip  flip);

	private:
		static std::map<std::string, SDL_Texture*> TileTexMap;
};

