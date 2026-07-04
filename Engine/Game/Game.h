#ifndef SDLPROJECT_GAME_H
#define SDLPROJECT_GAME_H

#include <SDL3/SDL.h>
#include <vector>
#include <algorithm>
#include "Core/Actor/Actor.h"
#include "Core/Camera/CameraComponent.h"
#include "../Editor/Camera/EditorCamera.h"
#include "Core/Scene/Scene.h"

class Game {
public:
    void Init(SDL_Renderer* renderer, Scene* scene);
    void Run();

    void ProcessEvents();
    void Update(float deltaTime);
    void Render();
    void RenderScene(EditorCamera* editorCamera);
    void Shutdown();

private:
    SDL_Renderer* m_Renderer    = nullptr;
    Scene*        m_Scene = nullptr;

    bool          m_IsRunning   = false;
};

#endif