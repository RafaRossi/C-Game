#ifndef SDLPROJECT_EDITOR_H
#define SDLPROJECT_EDITOR_H

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include <SDL3/SDL.h>
#include <vector>
#include <filesystem>

#include "Camera/EditorCamera.h"
#include "IconsFontAwesome6.h"
#include "PropertyType/PropertyType.h"

class Engine;
class Actor;
class Game;

class Editor {
public:
    explicit Editor(Engine* engine) : m_Engine(engine) {}

    void Init(SDL_Window* window, SDL_Renderer* renderer);
    void NewFrame();
    void Render();
    void ProcessEvent(const SDL_Event& event);
    void Shutdown();

    EditorCamera* GetEditorCamera() { return &m_EditorCamera; }

    void RenderSceneView();

private:
    Engine*       m_Engine   = nullptr;
    bool          m_IsRunning = false;
    Actor*        m_SelectedActor = nullptr;

    ImFont* m_FontDefault = nullptr;
    ImFont* m_FontLarge = nullptr;

    EditorCamera m_EditorCamera;

    std::string m_CurrentScenePath;
    Actor* m_CopiedActor;

    void RenderMainMenuBar();
    void RenderHierarchy();
    void RenderActorNode(Actor* actor);
    void RenderGameView();

    void RenderContentBrowser();

    void HandleShortcuts();
    void CreateNewScene();

    void SetupEngineStyle();

    void DrawInspector(const std::vector<ExposedField>& fields);
    void DrawInspectorForActor(Actor* actor);

    void OpenContextMenu(Actor* actor);

    Game* GetGame() const;

    Actor* CreateNewActorOnScene(Actor* parent);
    Actor* DuplicateActorOnScene(Actor *parent, Actor *source);

    void DrawGrid(Vector2 imageOrigin, Vector2 size);
    void DrawGizmo(Actor* actor, Vector2 imageOrigin);

    int m_GizmoDraggingAxis = -1;

    Vector2 m_GizmoDraggingStartMouse;
    Vector2 m_GizmoDragStartPos;

    std::string GetUniqueNameInHierarchy(Actor *parent, const std::string &baseName);

    std::string OpenFileDialog(const std::string &title, const std::vector<std::string> &filters);

    std::string SaveFileDialog(const std::string &title, const std::vector<std::string> &filters);

    void DrawDirectoryNodes(const std::filesystem::path& directoryPath);
};

#endif //SDLPROJECT_EDITOR_H