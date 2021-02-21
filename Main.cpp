#include "CApp.h"

CApp* game = nullptr;

int main(int argc, const char* argv[]) {

	const int FPS = 60; //pastovus frame rate
	const int frame_delay = 1000 / FPS; //Apskaičiuoja kiek turi užtrukti vienas frame 
	Uint32 frame_start; //Kiek laiko žaidimas veikia
	int frame_time;

	game = new CApp();
	game->OnInit("Hounted House", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

	while (game->Running()) {

		frame_start = SDL_GetTicks(); //kiek laiko praejo nuo žaidimo paleidimo

		game->OnEvent();
		game->OnUpdate();
		game->OnRender();

		frame_time = SDL_GetTicks() - frame_start; // kiek laiko užtrunka gauti event, updatinti juos ir renderinti juos t.y. kiek laiko užtrunka vienas frame
		if (frame_delay > frame_time) //tikrina ar frame rate yra greitesnis nei turi buti
		{
			SDL_Delay(frame_delay - frame_time); //delay'ina frames kiek reikia
		}
	}

	game->OnCleanup();
	return 0;
}