#pragma once
#include <SDL2/SDL_image.h>
#include <string>
#include <map>
#include "Engine.h"

class TextureManager
{
	public:
	static SDL_Texture* LoadTexture(const char* filename); //funkcija kuri uzkraus tekstura
	static SDL_Texture* LoadTileTexture(std::string id, std::string filename); //funkcija kuri uzkraus tile tekstura
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip  flip);
	static void DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip=SDL_FLIP_NONE);

	private:
		static std::map<std::string, SDL_Texture*> TileTexMap;
};

