#include "CApp.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include <iostream>

int count = 0;
GameObject* player;
GameObject* enemy;
Map* map;
SDL_Renderer* CApp::renderer = nullptr;

void CApp::OnInit(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
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

        player = new GameObject("Assets/Player/PlayerWalk/Walk-00.png", 0, 0); //sukuriamas zaidejas
        enemy = new GameObject("Assets/Enemy/tile000.png", 50, 50); //sukuriamas zaidejas
        map = new Map(); //sukuriamas map
    }
    else { 
       std::cout << "Something went wrong :(" << std::endl;
       isRunning = false; 
    }
}

void CApp::OnEvent()
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

void CApp::OnUpdate(){
    player->OnUpdate(80, 108);
    enemy->OnUpdate(102, 102);
}

void CApp::OnRender(){
    SDL_RenderClear(renderer); //Išvalomas renderis
    map->DrawMap();
    player->OnRender();
    enemy->OnRender();
    SDL_RenderPresent(renderer); //Atliktas renderinimas updatinamas
}

void CApp::OnCleanup(){
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit(); //Self explanatory
    std::cout << "Game cleaned <_<" << std::endl;
}

bool CApp::Running()
{
    return isRunning;
}


