#include <iostream>
#include "Constants.h"
#include "Engine.h"
#include "AssetManager.h"
#include "Map.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include "KeyboardControlComponent.h"
#include "TextLabelComponent.h"
#include "ProjectileEmitterComponent.h"
#include "glm/glm.hpp"

EntityManager manager;
AssetManager* Engine::assetManager = new AssetManager(&manager);
SDL_Renderer* Engine::renderer;
SDL_Event Engine::event;
SDL_Rect Engine::camera = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
Map* map;
bool isDebugMode = false;

Engine::Engine() {
    this->isRunning = false;
}

Engine::~Engine() {
}

bool Engine::IsRunning() const {
    return this->isRunning;
}

void Engine::Initialize(int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }
    if (TTF_Init() !=0) {
        std::cerr << "Error initializing SDL_ttf." << std::endl;
        return;
    }
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }

    LoadLevel(0);

    isRunning = true;
    return;
}


Entity& player(manager.AddEntity("chopper", PLAYER_LAYER));

void Engine::LoadLevel(int levelNumber) {
    /* Start including new assets to the assetmanager list */
    assetManager->AddTexture("tank-image", std::string("./assets/images/tank-big-right.png").c_str());
    assetManager->AddTexture("chopper-image", std::string("./assets/images/chopper-spritesheet.png").c_str());
    assetManager->AddTexture("radar-image", std::string("./assets/images/radar.png").c_str());
    assetManager->AddTexture("jungle-tiletexture", std::string("./assets/tilemaps/jungle.png").c_str());
    assetManager->AddTexture("heliport-image", std::string("./assets/images/heliport.png").c_str());
    assetManager->AddTexture("projectile-image", std::string("./assets/images/bullet-enemy.png").c_str());
    assetManager->AddFont("charriot-font", std::string("./assets/fonts/charriot.ttf").c_str(), 14);

    map = new Map("jungle-tiletexture", 2, 32);
    map->LoadMap("./assets/tilemaps/jungle.map", 25, 20);

    /* Start including entities and also components to them */
    player.AddComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
    player.AddComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
    player.AddComponent<KeyboardControlComponent>("up", "right", "down", "left", "space");
    player.AddComponent<ColliderComponent>("PLAYER", 240, 106, 32, 32);

    Entity& tankEntity(manager.AddEntity("tank", ENEMY_LAYER));
    tankEntity.AddComponent<TransformComponent>(150, 495, 10, 0, 32, 32, 1);
    tankEntity.AddComponent<SpriteComponent>("tank-image");

    tankEntity.AddComponent<ColliderComponent>("ENEMY", 150, 495, 32, 32);

    Entity& projectile(manager.AddEntity("projectile", PROJECTILE_LAYER));
    tankEntity.AddComponent<TransformComponent>(tankEntity.GetComponent<TransformComponent>()->position.x+ tankEntity.GetComponent<TransformComponent>()->width/2, tankEntity.GetComponent<TransformComponent>()->position.y + tankEntity.GetComponent<TransformComponent>()->height / 2, 0, 0, 4, 4, 1);
    tankEntity.AddComponent<SpriteComponent>("projectile-image");
    tankEntity.AddComponent<ColliderComponent>("PROJECTILE", tankEntity.GetComponent<TransformComponent>()->position.x + tankEntity.GetComponent<TransformComponent>()->width / 2, tankEntity.GetComponent<TransformComponent>()->position.y + tankEntity.GetComponent<TransformComponent>()->height / 2,  4, 4);
    tankEntity.AddComponent<ProjectileEmitterComponent>(50, 270, 200, true);

    Entity& heliport(manager.AddEntity("Heliport", OBSTACLE_LAYER));
    heliport.AddComponent<TransformComponent>(470, 420, 0, 0, 32, 32, 1);
    heliport.AddComponent<SpriteComponent>("heliport-image");
    heliport.AddComponent<ColliderComponent>("LEVEL_COMPLETE", 470, 420, 32, 32);

    Entity& radarEntity(manager.AddEntity("Radar", UI_LAYER));
    radarEntity.AddComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
    radarEntity.AddComponent<SpriteComponent>("radar-image", 8, 150, false, true);

    Entity& labelLevelName(manager.AddEntity("LabelLevelName", UI_LAYER));
    labelLevelName.AddComponent<TextLabelComponent>(10, 10, "First Level...", "charriot-font", WHITE_COLOR);

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
        if (event.key.keysym.sym == SDLK_F1) {
            if (!isDebugMode)
                isDebugMode = true;
            else
                isDebugMode = false;
        }   
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

    // Delta time is the difference in ticks from last frame converted to seconds
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

    // Clamp deltaTime to a maximum value
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    // Sets the new ticks for the current frame to be used in the next pass
    ticksLastFrame = SDL_GetTicks();

    manager.Update(deltaTime);

    if (isDebugMode)
        manager.DebugMode();

    HandleCameraMovement();
    CheckCollisions();// game loop check collisions
}

void Engine::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    if (manager.HasNoEntities()) {
        return;
    }

    manager.Render();
    manager.Render(isDebugMode);

    SDL_RenderPresent(renderer);
}

void Engine::HandleCameraMovement() {
    TransformComponent* mainPlayerTransform = player.GetComponent<TransformComponent>();

    camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);
    camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);

    camera.x = camera.x < 0 ? 0 : camera.x;
    camera.y = camera.y < 0 ? 0 : camera.y;
    camera.x = camera.x > camera.w ? camera.w : camera.x;
    camera.y = camera.y > camera.h ? camera.h : camera.y;
}

void Engine::CheckCollisions() {
    CollisionType collisionType = manager.CheckCollisions();

    if (collisionType == PLAYER_ENEMY_COLLISION) {
        ProcessGameOver();
    }
    if (collisionType == PLAYER_LEVEL_COMPLETE_COLLISION) {
        ProcessNextLevel(1);
    }
    if (collisionType == PLAYER_PROJECTILE_COLLISION)
    {
        ProcessGameOver();
    }
}

void Engine::ProcessNextLevel(int levelNumber) {
    std::cout << "Next Level" << std::endl;
    isRunning = false;
}

void Engine::ProcessGameOver() {
    std::cout << "Game Over" << std::endl;
    isRunning = false;
}

void Engine::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
