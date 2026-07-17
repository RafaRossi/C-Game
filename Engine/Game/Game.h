#ifndef SDLPROJECT_GAME_H
#define SDLPROJECT_GAME_H

#include <SDL3/SDL.h>
#include <vector>
#include <algorithm>
#include "Core/Actor/Actor.h"
#include "Core/Camera/CameraComponent.h"
#include "Core/Scene/Scene.h"

class Game {
public:
    static Game& Instance(){
        static Game instance;
        return instance;
    }

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    void Init(Scene *scene, SDL_Renderer* renderer);

    void ProcessEvents(SDL_Event event);

    void Update(float deltaTime);
    void LateUpdate(float deltaTime);

    Actor* CreateActor(const std::string& actorName);

    void Render();
    void Shutdown();

    SDL_Renderer* GetRenderer() { return m_Renderer; }
    Scene* GetScene() { return m_Scene; }

private:
    Game() = default;
    ~Game() = default;

    SDL_Renderer* m_Renderer    = nullptr;
    Scene*        m_Scene = nullptr;

    bool          m_IsRunning   = false;
};

#endif