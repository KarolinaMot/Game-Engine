#pragma once
#include "CApp.h"
class GameObject
{
	public:
		GameObject(const char* texture_sheet, int x, int y);  //objekto konstruktorius
		~GameObject(); //objekto dekonstruktorius
		void OnUpdate(int h, int w);
		void OnRender();
	private:
		int xpos; //objekto x pozicija lange
		int ypos; //objekto y pozicija lange
		SDL_Texture* obj_texture; //objekto tekstura t.y. nuotrauka
		SDL_Rect src_rect, dest_rect; //jo source ir destination staciakampiai, naudojami objekto teksturos atvaizdavimui
};

