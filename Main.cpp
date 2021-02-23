#include "Engine.h"

Engine* game = nullptr;

int main(int argc, const char* argv[]) {

	
	game = new Engine();
	game->OnInit("Hounted House", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

	while (game->Running()) {

		game->OnEvent(); //pagauna event
		game->OnUpdate(); //ivykdo event
		game->OnRender(); //renderina event
	}

	game->OnCleanup();
	return 0;
}