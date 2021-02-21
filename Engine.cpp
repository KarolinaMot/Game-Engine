#include "Engine.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"
#include <iostream>

int count = 0;
Map* map;
SDL_Renderer* Engine::renderer = nullptr;
Manager manager; //sukuriamas entity manager
auto& player(manager.addEntity()); //sukuriamas player


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
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //jei renderis susikure nustatoma jo piesimo spalva 
            std::cout << "Renderer created! OwO" << std::endl;
        }
        
        isRunning = true;

        map = new Map(); //sukuriamas map
        if (map)
            std::cout << "Map was created ;3"<<std::endl;


        //ECS implementacija
        
        player.addComponent<PositionComponent>(100, 500);
        player.addComponent<SpriteComponent>("Assets/Player/PlayerWalk/Walk-00.png");

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
    manager.refresh();
    manager.update();
}

void Engine::OnRender(){
    SDL_RenderClear(renderer); //Išvalomas renderis
    map->DrawMap();
    manager.draw();
    SDL_RenderPresent(renderer); //Atliktas renderinimas updatinamas
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


