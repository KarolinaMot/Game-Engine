#ifndef ENGINE_H
#define ENGINE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entity.h"
#include "Component.h"
#include "EntityManager.h"

class AssetManager;
class Engine {
private:
    bool isRunning;
    SDL_Window* window;
public:
    Engine();
    ~Engine();
    int ticksLastFrame = 0;
    bool IsRunning() const;
    static SDL_Renderer* renderer;
    static AssetManager* assetManager;
    void LoadLevel(int levelNumber);
    void Initialize(int width, int height);
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();
};

#endif
