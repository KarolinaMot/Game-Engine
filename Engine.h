#pragma once
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "Entity.h"
#include "Component.h"
#include "EntityManager.h"

class Engine{
    public:
        Engine() {}; //konstruktorius
        ~Engine() {}; //dekonstruktorius
        int ticks_last_frame = 0;
        void OnInit(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
        void OnEvent();
        void OnUpdate();
        void OnRender();
        void OnCleanup();
        bool Running();
        static SDL_Renderer* renderer;
        void LoadLevel(int levelNumber);

    private:        
        SDL_Window* window{};
        bool isRunning{};
   
};

