#include <iostream>
#include "./Constants.h"
#include "Engine.h"

int main(int argc, char* args[]) {
    Engine game;

    game.Initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

    while (game.IsRunning()) {
        game.ProcessInput();
        game.Update();
        game.Render();
    }

    game.Destroy();

    return 0;
}
