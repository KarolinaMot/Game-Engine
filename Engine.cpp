#include "Engine.h"
#include "TextureManager.h"
#include "Map.h"
#include <iostream>

EntityManager manager;
SDL_Renderer* Engine::renderer;

int count = 0;
Map* map;
SDL_Renderer* Engine::renderer = nullptr;

const unsigned int FPS = 60; //pastovus frame rate
const int frame_delay = 1000 / FPS; //Apskaičiuoja kiek turi užtrukti vienas frame 


void Engine::OnInit(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0; 
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {//Iniciuojamas SLD, tam kad galetume naudoti jo funkcijas

        std::cout << "SDL2 library initialized :)" << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);//sukuria langa, kuriame vyks zaidimas

        if (window) {//tikriname ar langas susikure

            std::cout << "Window created! UwU" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0); //Sukuriamas renderis, kuriam paduodamas langas, kuriame renderis kurs 
        if (renderer) {//tikriname ar renderis susikure
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //jei renderis susikure nustatomas background 
            std::cout << "Renderer created! OwO" << std::endl;
        }
        
        isRunning = true;

        map = new Map(); //sukuriamas map
        if (map)
            std::cout << "Map was created ;3"<<std::endl;

    }
    else { 
       std::cout << "Something went wrong :(" << std::endl;
       isRunning = false; 
    }
}

void Engine::OnEvent()
{
    SDL_Event event; //Sukuriamas kintamasis kuris laiko informacija apie events. Jis gali laikyti daug informacijos.
    SDL_PollEvent(&event); //isrenka paduoto event informacija
    switch (event.type) {//tikrinama kokio tipo event buvo padarytas
        case SDL_QUIT:
            isRunning = false;
            std::cout << "Quitting the game... bye! :((" << std::endl;
            break;
        default:
            break;
    }       
}

void Engine::OnUpdate(){
    int time_to_wait = frame_delay - (SDL_GetTicks() - ticks_last_frame);

    if (time_to_wait > 0 && time_to_wait <= frame_delay) { //Wait until 16 ms has ellapsed since the last frame   
        SDL_Delay(time_to_wait);  }

    float delta_time = (SDL_GetTicks() - ticks_last_frame) / 1000.0f; //Delta time is the difference in ticks from last frame converted to seconds
    delta_time = (delta_time > 0.05f) ? 0.05f : delta_time; //Giving delta time a max value so debugging the program won't mess everything up
    ticks_last_frame = SDL_GetTicks(); //Sets the ticks from the current frame to be used in the next pass
}

void Engine::OnRender(){
    SDL_RenderClear(renderer); //Išvalomas renderis
    map->DrawMap();
    SDL_RenderPresent(renderer); //Atliktas renderinimas updatinamas, swaps front and back buffers
}

void Engine::OnCleanup(){
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit(); //Self explanatory
    std::cout << "Game cleaned <_<" << std::endl;
}

bool Engine::Running()
{
    return isRunning;
}

void Engine::LoadLevel(int levelNumber)
{
}


