#ifndef SDLPROJECT_EDITOR_H
#define SDLPROJECT_EDITOR_H

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

#include "../Core/Game/Game.h"
#include "Reflection/Reflection.h"

class Editor {

public:
    Editor(Game* game) : m_Game(game) {
        Init();
    }

    void Run();

private:
    Game* m_Game = nullptr;

    SDL_Window*   m_Window      = nullptr;
    SDL_Renderer* m_Renderer    = nullptr;
    bool          m_IsRunning   = false;

    void Init();
    void NewFrame();

    void Render();
    void ProcessEvent();

    void Shutdown();

    void RenderMainMenuBar();
    void DrawInspector(void* instance, ClassMetadata& meta);
};


#endif //SDLPROJECT_EDITOR_H
