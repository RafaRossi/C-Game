#include "Engine.h"
#include "Editor/Editor.h"
#include <iostream>

constexpr int WINDOW_WIDTH  = 1024;
constexpr int WINDOW_HEIGHT = 768;

Engine::Engine() = default;

Engine::~Engine() {
    Shutdown();
}

void Engine::Init() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Erro SDL3: " << SDL_GetError() << std::endl;
        return;
    }

    if (!SDL_CreateWindowAndRenderer("TR Engine", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE,
                                     &m_Window, &m_Renderer)) {
        std::cerr << "Erro ao criar janela/renderer: " << SDL_GetError() << std::endl;
        return;
    }

    m_Scene = new Scene();

    m_Editor = new Editor(this);
    m_Editor->Init(m_Window, m_Renderer);

    m_ViewportTexture = SDL_CreateTexture(m_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, m_ViewportWidth, m_ViewportHeight);

    m_LastTime  = SDL_GetTicks();
    m_IsRunning = true;
}

void Engine::Run() {
    while (m_IsRunning) {
        ProcessEvents();

        m_Editor->NewFrame();

        Update();
        Render();
    }
}

void Engine::Shutdown() {
    if (m_Game != nullptr) {
        m_Game->Shutdown();
        delete m_Game;
        m_Game = nullptr;
    }

    if (m_Editor != nullptr) {
        m_Editor->Shutdown();
        delete m_Editor;
        m_Editor = nullptr;
    }

    if(m_ViewportTexture != nullptr){
        SDL_DestroyTexture(m_ViewportTexture);
        m_ViewportTexture = nullptr;
    }

    if(m_GameViewTexture != nullptr){
        SDL_DestroyTexture(m_GameViewTexture);
        m_GameViewTexture = nullptr;
    }

    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

void Engine::Play() {
    if (m_IsPlaying) return;

    m_Scene->Serialize();

    m_Game = new Game();
    m_Game->Init(m_Renderer, m_Scene);

    m_IsPlaying = true;
    m_IsPaused  = false;

    m_GameViewTexture = SDL_CreateTexture(m_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, m_GameViewWidth, m_GameViewHeight);
}

void Engine::ResizeViewport(int w, int h) {
    if(m_ViewportWidth == w && m_ViewportHeight == h) return;

    m_ViewportWidth = w;
    m_ViewportHeight = h;

    if(m_ViewportTexture != nullptr)
        SDL_DestroyTexture(m_ViewportTexture);

    m_ViewportTexture = SDL_CreateTexture(m_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
}

void Engine::ResizeGameView(int w, int h) {
    if(m_GameViewWidth == w && m_GameViewHeight == h) return;

    m_GameViewWidth = w;
    m_GameViewHeight = h;

    if(m_GameViewTexture != nullptr)
        SDL_DestroyTexture(m_GameViewTexture);

    m_GameViewTexture = SDL_CreateTexture(m_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
}

void Engine::Stop() {
    if (!m_IsPlaying) return;

    m_Game->Shutdown();
    delete m_Game;
    m_Game = nullptr;

    m_Scene->Deserialize();

    m_IsPlaying = false;
    m_IsPaused  = false;
}

void Engine::Pause() {
    if (!m_IsPlaying) return;
    m_IsPaused = !m_IsPaused;
}

float Engine::CalculateDeltaTime() {
    Uint64 current = SDL_GetTicks();
    float dt = (current - m_LastTime) / 1000.0f;
    m_LastTime = current;
    return dt;
}

void Engine::ProcessEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        m_Editor->ProcessEvent(event);

        if (event.type == SDL_EVENT_QUIT)
            m_IsRunning = false;
    }
}

void Engine::Update() {
    if (m_IsPlaying && !m_IsPaused && m_Game != nullptr)
        m_Game->Update(CalculateDeltaTime());
}

void Engine::Render() {

    if (m_ViewportTexture != nullptr) SDL_DestroyTexture(m_ViewportTexture);
    m_ViewportTexture = SDL_CreateTexture(m_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, m_ViewportWidth, m_ViewportHeight);

    if (m_GameViewTexture != nullptr) SDL_DestroyTexture(m_GameViewTexture);
    m_GameViewTexture = SDL_CreateTexture(m_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, m_GameViewWidth, m_GameViewHeight);

    SDL_SetRenderDrawColor(m_Renderer, 30, 30, 30, 255);
    SDL_RenderClear(m_Renderer);

    SDL_SetRenderTarget(m_Renderer, m_ViewportTexture);
    SDL_SetRenderDrawColor(m_Renderer, 20, 30, 45, 255);
    SDL_RenderClear(m_Renderer);

    if(m_Game != nullptr)
        m_Game->RenderScene(m_Editor->GetEditorCamera());

    SDL_SetRenderTarget(m_Renderer, nullptr);

    SDL_SetRenderTarget(m_Renderer, m_GameViewTexture);
    SDL_SetRenderDrawColor(m_Renderer, 20, 30, 45, 255);
    SDL_RenderClear(m_Renderer);

    if (m_IsPlaying && m_Game != nullptr)
        m_Game->Render();

    SDL_SetRenderTarget(m_Renderer, nullptr);

    m_Editor->Render();

    SDL_RenderPresent(m_Renderer);
}
