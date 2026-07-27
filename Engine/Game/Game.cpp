#include <stdexcept>
#include "Game.h"
#include "Core/Inputs/InputManager.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Texture/TextureManager.h"
#include "Engine/Game/Core/Physics/PhysicsManager.h"


void Game::ProcessEvents(SDL_Event event) {
    InputManager::Instance().ProcessEvent(event);

    if (event.type == SDL_EVENT_QUIT)
        m_IsRunning = false;

    if (InputManager::Instance().IsKeyPressed(SDL_SCANCODE_ESCAPE))
        m_IsRunning = false;
}

void Game::Start() {
    for (auto* actor : m_Scene->GetActors()){
        if(!actor->IsActive()) continue;

        actor->Start();
    }
}

void Game::Update(float deltaTime) {
    m_Scene->ProcessPendingActors();

    for (auto* actor : m_Scene->GetActors()){
        if(!actor->IsActive()) continue;

        actor->Update(deltaTime);
    }

    PhysicsManager::Update(deltaTime);
}

void Game::LateUpdate(float deltaTime) {

    auto& actors = m_Scene->GetActors();

    for(auto it = actors.begin(); it != actors.end(); ){
        Actor* actor = *it;

        if(actor->IsPendingDestroy()){
            delete actor;
            it = actors.erase(it);
        }
        else{
            if(actor->IsActive()){
                actor->LateUpdate(deltaTime);
            }
            ++it;
        }
    }
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

        if(!actor -> IsActive() ) continue;
        auto* renderer = actor->GetComponent<Renderer>();

        if(!renderer) continue;

        bool isVisible = camera->cullingMask & (int)actor->layer;

        if(isVisible) {
            renderer->Draw();
        }
    }

    SDL_SetRenderScale(m_Renderer, 1.0f, 1.0f);
    SDL_SetRenderViewport(m_Renderer, nullptr);
}

void Game::Shutdown() {
    TextureManager::Instance().UnloadAll();

    m_Scene = nullptr;
    m_Renderer = nullptr;
}

void Game::Init(Scene *scene, SDL_Renderer* renderer) {
    m_Scene = scene;
    m_Renderer = renderer;

    SetSeed(9999);

    m_Scene->InitializeScene();

    PhysicsManager::Init();
}

Actor* Game::CreateActor(const std::string& actorName)
{
    return m_Scene->CreateActor(actorName);
}

void Game::SetSeed(unsigned int seed) {
    m_CurrentSeed = seed;
    m_Rng.seed(seed);
}

int Game::GetRandomInt(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(m_Rng);
}

float Game::GetRandomFloat(float min, float max) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(m_Rng);
}

void Game::GenerateRandomSeed() {
    std::random_device rd;
    unsigned int randomSeed = rd();

    SetSeed(randomSeed);
}