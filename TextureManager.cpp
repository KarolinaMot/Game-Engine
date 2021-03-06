#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* filename) //funkcija, kuriai padavius texture ir renderer, atvaizduoja nuotrauka
{
	SDL_Surface* temp_surface = IMG_Load(filename); //sukuriama laikinas pavirsius, kuriam priduodama reiksme kaip nuotrauka
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Engine::renderer, temp_surface); // SDL_CreateTextureFromSurface pavirsiu pavercia i surface
	SDL_FreeSurface(temp_surface); //laikinas pavirsius yra isvalomas sekanciam naudojimui

	return tex;
}

SDL_Texture* TextureManager::LoadTileTexture(std::string id, std::string filename)
{
	SDL_Surface* temp_surface = IMG_Load(filename.c_str()); //sukuriama laikinas pavirsius, kuriam priduodama reiksme kaip nuotrauka
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Engine::renderer, temp_surface); // SDL_CreateTextureFromSurface pavirsiu pavercia i surface
	SDL_FreeSurface(temp_surface); //laikinas pavirsius yra isvalomas sekanciam naudojimui
	TileTexMap[id] = tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Engine::renderer, tex, &src, &dest, 0.0, NULL, flip); 
}

void TextureManager::DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip)
{
	SDL_Rect dstRect;
		dstRect.x = x;
		dstRect.y = y;
		dstRect.h = tileSize;
		dstRect.w = tileSize;
	SDL_Rect srcRect;
		srcRect.x = tileSize*frame;
		srcRect.y = tileSize * row;
		srcRect.h = tileSize;
		srcRect.w = tileSize;
	SDL_RenderCopyEx(Engine::renderer, TileTexMap[tilesetID], &srcRect, &dstRect, 0, 0, flip);
}
