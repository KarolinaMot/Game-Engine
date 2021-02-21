#pragma once
#define SDL_MAIN_HANDLED
#include <SDL.h>

class CApp{
    public:
        CApp() {}; //konstruktorius
        ~CApp() {}; //dekonstruktorius
        void OnInit(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
        void OnEvent();
        void OnUpdate();
        void OnRender();
        void OnCleanup();
        bool Running();
        static SDL_Renderer* renderer;

    private:        
        SDL_Window* window{};
        bool isRunning{};
   
};

