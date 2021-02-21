#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* texture_sheet, int x, int y)//gameObject kurimas
{
	obj_texture = TextureManager::LoadTexture(texture_sheet); //sukuriam objekto tekstura su textureManager, kuriam priduodam texturesheet ir renderi

	xpos = x;
	ypos = y;
}

GameObject::~GameObject()
{
}

void GameObject::OnUpdate(int h, int w) //judejimo kodas
{
	xpos++;
	ypos++;

	src_rect.h = h;
	src_rect.w = w;
	src_rect.x = 0;
	src_rect.y = 0;

	dest_rect.x = xpos;
	dest_rect.y = ypos;
	dest_rect.w = src_rect.w;
	dest_rect.h = src_rect.h;
}

void GameObject::OnRender() //objekto atvaizdavimas, sukurimas 
{
	SDL_RenderCopy(CApp::renderer, obj_texture, &src_rect, &dest_rect);

}
