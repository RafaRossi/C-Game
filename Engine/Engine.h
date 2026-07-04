#ifndef SDLPROJECT_ENGINE_H
#define SDLPROJECT_ENGINE_H

#include <SDL3/SDL.h>
#include "Game/Game.h"

class Editor;

class Engine {
public:
    Engine();
    ~Engine();

    void Init();
    void Run();
    void Shutdown();

    void Play();
    void Stop();
    void Pause();

    bool IsPlaying() const { return m_IsPlaying; }
    bool IsPaused()  const { return m_IsPaused;  }

    SDL_Renderer* GetRenderer() const { return m_Renderer; }
    SDL_Window*   GetWindow()   const { return m_Window;   }
    Game*         GetGame()     const { return m_Game;     }

    SDL_Texture* GetGameViewTexture() const { return m_GameViewTexture; }
    void ResizeGameView(int w, int h);

    SDL_Texture* GetViewportTexture() const { return m_ViewportTexture; }
    void ResizeViewport(int w, int h);

    Scene* GetScene() const { return m_Scene; }

private:
    void ProcessEvents();
    void Update();
    void Render();
    float CalculateDeltaTime();

    SDL_Window*   m_Window    = nullptr;
    SDL_Renderer* m_Renderer  = nullptr;
    bool          m_IsRunning = false;
    bool          m_IsPlaying = false;
    bool          m_IsPaused  = false;
    Uint64        m_LastTime  = 0;

    Scene* m_Scene   = nullptr;
    Game*   m_Game   = nullptr;
    Editor* m_Editor = nullptr;

    SDL_Texture* m_GameViewTexture = nullptr;
    int m_GameViewWidth = 800;
    int m_GameViewHeight = 600;

    SDL_Texture* m_ViewportTexture = nullptr;
    int m_ViewportWidth = 800;
    int m_ViewportHeight = 600;
};

#endif //SDLPROJECT_ENGINE_H