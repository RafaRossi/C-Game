#ifndef SDLPROJECT_GAME_H
#define SDLPROJECT_GAME_H

#include <SDL3/SDL.h>
#include <vector>
#include <algorithm>
#include "../Actor/Actor.h"
#include "../Camera/CameraComponent.h"

class Game {
public:
    Game();
    ~Game();

    void Run();

    Actor* CreateActor();
    void RemoveActor(Actor* actor);

    Actor* GetCameraActor() const { return m_CameraActor; }
    CameraComponent* GetCamera() const { return m_CameraActor->GetComponent<CameraComponent>(); }

private:
    void Init();
    void ProcessEvents();
    void Update(float deltaTime);
    void Render();
    void Shutdown();

    SDL_Window*   m_Window      = nullptr;
    SDL_Renderer* m_Renderer    = nullptr;
    bool          m_IsRunning   = false;
    bool          m_LayerOrderDirty = true;

    Actor* m_CameraActor = nullptr;
    std::vector<Actor*> m_Actors;
};

#endif