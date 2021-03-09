#include <iostream>
#include "Constants.h"
#include "Engine.h"
#include "AssetManager.h"
#include "Map.h"
#include "EntityManager.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "KeyboardControlComponent.h"
#include "glm/glm.hpp"

EntityManager manager;
AssetManager* Engine::assetManager = new AssetManager(&manager);
SDL_Renderer* Engine::renderer;
SDL_Event Engine::event;
SDL_Rect Engine::camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
Map* map;

Engine::Engine() { //engine constructor
    this->isRunning = false;
}

Engine::~Engine() {
}

bool Engine::IsRunning() {
    return this->isRunning;
}

void Engine::Initialize(int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { //if sld libraries initialized
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }
    window = SDL_CreateWindow( //creates window
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_BORDERLESS
    );
    if (!window) { //checks if window was created succesfully
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, 0); //creates a renderer
    if (!renderer) { //checks if renderer was created
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }

    LoadLevel(0); //loads a level

    isRunning = true;
    return;
}
Entity& player(manager.AddEntity("Player", PLAYER_LAYER)); //Creates a player entity and adds it to the entity manager
void Engine::LoadLevel(int levelNumber) { //function used to run level
    assetManager->AddTexture("player_image", std::string("Assets/Player/Run.png").c_str()); //Adds a texture to the asset manager
    assetManager->AddTexture("jungle-tiletexture", std::string("Assets/Maps/Tiles/jungle.png").c_str());

    map = new Map("jungle-tiletexture", 2, 32);
    map->LoadMap("Assets/Maps/jungle.map", 25, 20);

    
    player.AddComponent<TransformComponent>(0, 0, 0, 0, 49, 43, 2); //adds transform ccomponent to player
    player.AddComponent<SpriteComponent>("player_image", 8, 80, false, false ); //adds sprite component and animation to player
    player.AddComponent<KeyboardControlComponent>(80, false, false, true, true, 20, 25);

    manager.ListAllEntities(); 

}

void Engine::ProcessInput() {
    
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT: {
            isRunning = false;
            break;
        }
        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                isRunning = false;
            }
            break;
        }
        default: {
            break;
        }
    }
}

void Engine::Update() {
    // Waste some time / sleep until we reach the target frame time in milliseconds
    int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);

    // Only sleep if we are too fast
    if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) {
        SDL_Delay(timeToWait);
    }

    // Delta time is the difference in ticks from last frame converted to secomds
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

    // Clamp deltaTime to a maximum value
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    // Sets the new ticks for the current frame to be used in the next pass
    ticksLastFrame = SDL_GetTicks();

    manager.Update(deltaTime);

    HandleCameraMovement();
}

void Engine::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    if (manager.HasNoEntities()) {
        return;
    }

    manager.Render();

    SDL_RenderPresent(renderer);
}

void Engine::HandleCameraMovement() {
    TransformComponent* mainPlayerTransform = player.GetComponent<TransformComponent>();
    camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);
    camera.y= mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);

    //Clamps values of camera
    camera.x = camera.x < 0 ? 0 : camera.x;
    camera.x = camera.x > camera.w ? camera.w : camera.x;
    camera.y = camera.y < 0 ? 0 : camera.y;
    camera.y = camera.y > camera.h ? camera.h : camera.y;
}

void Engine::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
