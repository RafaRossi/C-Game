#ifndef SDLPROJECT_EDITOR_H
#define SDLPROJECT_EDITOR_H

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include <SDL3/SDL.h>

#include "Reflection/Reflection.h"
#include "Camera/EditorCamera.h"
#include "IconsFontAwesome6.h"

class Engine;
class Actor;
class Game;
struct ClassMetadata;

class Editor {
public:
    explicit Editor(Engine* engine) : m_Engine(engine) {}

    void Init(SDL_Window* window, SDL_Renderer* renderer);
    void NewFrame();
    void Render();
    void ProcessEvent(const SDL_Event& event);
    void Shutdown();

    EditorCamera* GetEditorCamera() { return &m_EditorCamera; }
    void RenderSceneView(); // ← novo

private:
    Engine*       m_Engine   = nullptr;
    bool          m_IsRunning = false;
    Actor*        m_SelectedActor = nullptr;

    ImFont* m_FontDefault = nullptr;
    ImFont* m_FontLarge = nullptr;

    EditorCamera m_EditorCamera;

    void RenderMainMenuBar();
    void RenderHierarchy();
    void RenderActorNode(Actor* actor);
    void RenderGameView();

    void SetupEngineStyle();

    void DrawInspector(void* instance, ClassMetadata& meta);
    void DrawInspectorForActor(Actor* actor);

    void OpenContextMenu(Actor* actor);

    Game* GetGame() const;

    Actor* CreateActorOnScene(Actor* parent);
    Actor* CreateActorOnScene(Actor *parent, Actor *source);
};

#endif //SDLPROJECT_EDITOR_H