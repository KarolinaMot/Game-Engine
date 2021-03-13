#include <iostream>
#include "Constants.h"
#include "Engine.h"

int main(int argc, char* args[]) {
    Engine game; //Creates game object

    game.Initialize(WINDOW_WIDTH, WINDOW_HEIGHT); //Initializes game window

    while (game.IsRunning()) {
        game.ProcessInput();
        game.Update();
        game.Render();
    }

    game.Destroy();

    return 0;
}
