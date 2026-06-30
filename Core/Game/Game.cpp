//
// Created by rossi on 29/06/2026.
//
#include "Game.h"
#include "../../Utils/Utils.h"
#include <iostream>
#include <algorithm>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

Game::Game() {
    Init();
}

void Game::Init() {
    if(!SDL_Init(SDL_INIT_VIDEO)){
        std::cerr << "Erro SDL3: " << SDL_GetError() << std::endl;
        return;
    }

    if(!SDL_CreateWindowAndRenderer("Card Core", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &m_Window, &m_Renderer)){
        std::cerr<< "Erro ao criar Janela/Renderer: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    m_IsRunning = true;
}

void Game::ProcessEvents() {
    SDL_Event event;

    while (SDL_PollEvent(&event)){
        if(event.type == SDL_EVENT_QUIT)
            m_IsRunning = false;
        if(event.type == SDL_EVENT_KEY_DOWN)
            if(event.key.key == SDLK_ESCAPE)
                m_IsRunning = false;
    }
}

void Game::Update(float deltaTime) {
    for(auto* actor : m_Actors)
        actor->Update(deltaTime);
}

void Game::Render() {
    if(m_LayerOrderDirty){
        std::sort(m_Actors.begin(), m_Actors.end(), [](Actor* a, Actor* b){
            return a->renderer.orderInLayer < b->renderer.orderInLayer;
        });
        m_LayerOrderDirty = false;
    }

    SDL_Color bg = {20, 30, 45, 255};
    SetRenderDrawColor(m_Renderer, bg);
    SDL_RenderClear(m_Renderer);

    for (auto* actor : m_Actors)
        actor->Draw(m_Renderer);

    SDL_RenderPresent(m_Renderer);
}

void Game::Shutdown() {
    for(auto* actor : m_Actors)
        delete actor;

    m_Actors.clear();

    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

void Game::Run() {
    Uint64 lastTime = SDL_GetTicks();

    while(m_IsRunning){
        Uint64 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;

        lastTime = currentTime;

        ProcessEvents();
        Update(deltaTime);
        Render();
    }
}

Actor* Game::CreateActor(){
    auto actor = new Actor();

    m_Actors.push_back(actor);
    m_LayerOrderDirty = true;
    return actor;
}

Game::~Game() {
    Shutdown();
}