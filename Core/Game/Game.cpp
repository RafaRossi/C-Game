#include "Game.h"
#include "../Inputs/InputManager.h"
#include <iostream>
#include "../Renderer/Renderer.h"

constexpr int WINDOW_WIDTH  = 800;
constexpr int WINDOW_HEIGHT = 600;

Game::Game() {
    Init();
}

Game::~Game() {
    Shutdown();
}

void Game::Init() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Erro SDL3: " << SDL_GetError() << std::endl;
        return;
    }

    if (!SDL_CreateWindowAndRenderer("Engine", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &m_Window, &m_Renderer)) {
        std::cerr << "Erro ao criar Janela/Renderer: " << SDL_GetError() << std::endl;
        return;
    }

    m_CameraActor = CreateActor();
    m_CameraActor->AddComponent<CameraComponent>();

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
    for (auto* actor : m_Actors)
        actor->Update(deltaTime);
}

void Game::Render() {
    if (m_LayerOrderDirty) {
        std::sort(m_Actors.begin(), m_Actors.end(), [](Actor* a, Actor* b) {
            auto* srA = a->GetComponent<Renderer>();
            auto* srB = b->GetComponent<Renderer>();

            int layerA = srA ? srA->orderInLayer : 0;
            int layerB = srB ? srB->orderInLayer : 0;

            return layerA < layerB;
        });
        m_LayerOrderDirty = false;
    }

    GetCamera()->Apply(m_Renderer);

    for (auto* actor : m_Actors)
        actor->Draw(m_Renderer);

    SDL_SetRenderScale(m_Renderer, 1.0f, 1.0f);
    SDL_SetRenderViewport(m_Renderer, nullptr);

    SDL_RenderPresent(m_Renderer);
}

void Game::Shutdown() {
    for (auto* actor : m_Actors)
        delete actor;
    m_Actors.clear();

    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
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

Actor* Game::CreateActor() {
    Actor* actor = new Actor();
    m_Actors.push_back(actor);
    m_LayerOrderDirty = true;
    return actor;
}

void Game::RemoveActor(Actor* actor) {
    if (actor == nullptr) return;

    if (actor->parent != nullptr)
        actor->parent->RemoveChild(actor);

    for (auto* child : actor->children)
        child->parent = nullptr;

    auto it = std::find(m_Actors.begin(), m_Actors.end(), actor);
    if (it != m_Actors.end()) {
        delete *it;
        m_Actors.erase(it);
        m_LayerOrderDirty = true;
    }
}