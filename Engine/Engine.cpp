#include "Engine.h"
#include "Editor/Editor.h"
#include "Sandbox/Assets/Scripts/GameplayScene.h"
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


#ifdef TR_EDITOR
    m_Editor = new Editor(this);
    m_Editor->Init(m_Window, m_Renderer);

    if(!SceneSerializer::LoadScene(m_Scene = new Scene(), "../Scenes/Default Scene.tscene"))
    {
        auto* cameraActor = m_Scene->CreateActor("Main Camera");
        auto* cameraComponent = cameraActor->AddComponent<CameraComponent>();

        m_Scene->SetMainCamera(cameraComponent);

        SceneSerializer::SaveScene(m_Scene, "../Scenes/Default Scene.tscene");
    }

#else
    m_IsPlaying = true;
    m_Scene = new GameplayScene();

    m_GameViewTexture = SDL_CreateTexture(m_Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);
#endif

    m_LastTime  = SDL_GetTicks();
    m_IsRunning = true;

}

void Engine::Run() {
    Game::Instance().Init(m_Scene, m_Renderer);

    while (m_IsRunning) {
        ApplySceneChange();

        ProcessEvents();

#ifdef TR_EDITOR
        m_Editor->NewFrame();
#endif
        Update();
        Render();
    }
}

void Engine::Shutdown() {
    delete m_Scene;
    m_Scene = nullptr;

    m_IsRunning = false;

#ifdef TR_EDITOR
    if (m_Editor != nullptr) {
        m_Editor->Shutdown();
        delete m_Editor;
        m_Editor = nullptr;
    }
#endif

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
        Game::Instance().ProcessEvents(event);
#ifdef TR_EDITOR
        m_Editor->ProcessEvent(event);
#endif
        if (event.type == SDL_EVENT_QUIT)
            m_IsRunning = false;
    }
}

void Engine::Update() {
    if (m_IsPlaying && !m_IsPaused)
        Game::Instance().Update(CalculateDeltaTime());
}

void Engine::Render() {
    SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_Renderer);

    SDL_SetRenderTarget(m_Renderer, m_GameViewTexture);
    Game::Instance().Render();
    SDL_SetRenderTarget(m_Renderer, nullptr);

    int winW, winH;
    SDL_GetCurrentRenderOutputSize(m_Renderer, &winW, &winH);

    float scaleX = (float)winW / WINDOW_WIDTH;
    float scaleY = (float)winH / WINDOW_HEIGHT;
    float scale  = std::min(scaleX, scaleY);

    float destW = WINDOW_WIDTH  * scale;
    float destH = WINDOW_HEIGHT * scale;
    float destX = (winW - destW) / 2.0f;
    float destY = (winH - destH) / 2.0f;

    SDL_FRect dest = {destX, destY, destW, destH};
    SDL_RenderTexture(m_Renderer, m_GameViewTexture, nullptr, &dest);

    SDL_RenderPresent(m_Renderer);
}

void Engine::ChangeScene(Scene *scene) {
    if(scene == nullptr) return;

#ifdef TR_EDITOR
    if (m_Editor != nullptr)
        m_Editor->OnSceneChanged();
#endif

    m_NextScene = scene;
}

void Engine::ApplySceneChange() {
    if(m_NextScene == nullptr) return;

    delete m_Scene;

    m_Scene = m_NextScene;
    m_NextScene = nullptr;
}
