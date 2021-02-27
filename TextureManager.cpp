#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* filename) //funkcija, kuriai padavius texture ir renderer, atvaizduoja nuotrauka
{
	SDL_Surface* temp_surface = IMG_Load(filename); //sukuriama laikinas pavirsius, kuriam priduodama reiksme kaip nuotrauka
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Engine::renderer, temp_surface); // SDL_CreateTextureFromSurface pavirsiu pavercia i surface
	SDL_FreeSurface(temp_surface); //laikinas pavirsius yra isvalomas sekanciam naudojimui

	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Engine::renderer, tex, &src, &dest, 0.0, NULL, flip); 
}