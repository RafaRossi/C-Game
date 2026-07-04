#include "Game.h"
#include "Core/Inputs/InputManager.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Texture/TextureManager.h"

constexpr int WINDOW_WIDTH  = 800;
constexpr int WINDOW_HEIGHT = 600;

void Game::Init(SDL_Renderer* renderer, Scene* scene) {
    m_Renderer = renderer;
    m_Scene = scene;

    TextureManager::Instance().Init(m_Renderer);

    m_IsRunning = true;
}

void Game::ProcessEvents() {
    InputManager::Instance().NewFrame();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        InputManager::Instance().ProcessEvent(event);

        if (event.type == SDL_EVENT_QUIT)
            m_IsRunning = false;
    }

    if (InputManager::Instance().IsKeyPressed(SDL_SCANCODE_ESCAPE))
        m_IsRunning = false;
}

void Game::Update(float deltaTime) {
    for (auto* actor : m_Scene->GetActors())
        actor->Update(deltaTime);
}

void Game::Render() {
    auto* camera = m_Scene->GetCamera();

    if (m_Scene->IsLayerOrderDirty()) {
        std::sort(m_Scene->GetActors().begin(), m_Scene->GetActors().end(), [](Actor* a, Actor* b) {
            auto* srA = a->GetComponent<Renderer>();
            auto* srB = b->GetComponent<Renderer>();

            int layerA = srA ? srA->orderInLayer : 0;
            int layerB = srB ? srB->orderInLayer : 0;

            return layerA < layerB;
        });
        m_Scene->SetLayerOrderDirty(false);
    }

    camera->Apply(m_Renderer);

    for (auto* actor : m_Scene->GetActors()){
        if(!actor -> IsActive()) continue;

        bool isVisible = camera->cullingMask & (int)actor->layer;

        if(isVisible)
            actor->Draw(m_Renderer);
    }

    SDL_SetRenderScale(m_Renderer, 1.0f, 1.0f);
    SDL_SetRenderViewport(m_Renderer, nullptr);
}

void Game::Shutdown() {
    TextureManager::Instance().UnloadAll();

    m_Scene = nullptr;
    m_Renderer = nullptr;
}

void Game::Run() {
    Uint64 lastTime = SDL_GetTicks();

    while (m_IsRunning) {
        Uint64 currentTime = SDL_GetTicks();
        float deltaTime    = (currentTime - lastTime) / 1000.0f;
        lastTime           = currentTime;

        ProcessEvents();
        Update(deltaTime);
        Render();
    }
}

void Game::RenderScene(EditorCamera *editorCamera) {
    editorCamera->Apply(m_Renderer);

    for (auto* actor : m_Scene->GetActors()) {
        if (!actor->IsActive()) continue;
        actor->Draw(m_Renderer);
    }

    SDL_SetRenderScale(m_Renderer, 1.0f, 1.0f);
    SDL_SetRenderViewport(m_Renderer, nullptr);
}
