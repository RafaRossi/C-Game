#include "Editor.h"
#include "../Engine.h"  // Engine precisa do header completo aqui
#include <iostream>

void Editor::Init(SDL_Window* window, SDL_Renderer* renderer) {
    const char* basePath = SDL_GetBasePath();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    if (basePath) {
        std::string fontPath = std::string(basePath) + "Editor/Fonts/Roboto/static/Roboto-Black.ttf";
        io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 16.f);
    } else {
        io.Fonts->AddFontFromFileTTF("Editor/Fonts/Roboto/static/Roboto-Black.ttf", 16.f);
    }

    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);
}

void Editor::NewFrame() {
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void Editor::Render() {
    RenderMainMenuBar();
    RenderHierarchy();
    RenderSceneView();
    RenderGameView();

    DrawInspectorForActor(m_SelectedActor);

    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), m_Engine->GetRenderer());
}

void Editor::ProcessEvent(const SDL_Event& event) {
    ImGui_ImplSDL3_ProcessEvent(&event);
}

void Editor::Shutdown() {
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}

Game* Editor::GetGame() const {
    return m_Engine->GetGame();
}

void Editor::RenderMainMenuBar() {
    ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImColor(30, 30, 30).Value);

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) { ImGui::EndMenu(); }

        if (ImGui::BeginMenu("Actors")) {
            if (ImGui::MenuItem("Actor")){
                CreateActorOnScene(nullptr);
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit")) { ImGui::EndMenu(); }

        if (ImGui::BeginMenu("Window")) { ImGui::EndMenu(); }

        ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 2.0f - 50.0f);

        if (!m_Engine->IsPlaying()) {
            if (ImGui::Button("  ▶ Play  "))
                m_Engine->Play();
        } else {
            if (ImGui::Button("  ■ Stop  "))
                m_Engine->Stop();
            ImGui::SameLine();
            if (ImGui::Button("  ⏸ Pause  "))
                m_Engine->Pause();
        }

        ImGui::EndMainMenuBar();
    }

    ImGui::PopStyleColor();
}

void Editor::RenderHierarchy() {
    ImGui::Begin("Hierarchy");

    Scene* scene = m_Engine->GetScene();

    if (scene == nullptr) {
        ImGui::TextDisabled("Nenhuma cena carregada");
        ImGui::End();
        return;
    }

    for (auto* actor : scene->GetActors()) {
        if (actor->parent != nullptr) continue;
        RenderActorNode(actor);
    }

    ImGui::End();
}

void Editor::RenderGameView() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin("Game");

    ImVec2 size = ImGui::GetContentRegionAvail();

    if (size.x > 0 && size.y > 0) {
        m_Engine->ResizeGameView((int) size.x, (int) size.y);
    }

    SDL_Texture* tex = m_Engine->GetGameViewTexture();
    if (tex != nullptr) {
        ImGui::Image(
                (ImTextureID)tex,
                size
        );
    }

    ImGui::End();
    ImGui::PopStyleVar();
}

void Editor::RenderActorNode(Actor* actor) {
    ImGuiTreeNodeFlags flags =
            ImGuiTreeNodeFlags_OpenOnArrow |
            ImGuiTreeNodeFlags_SpanAvailWidth;

    if (actor == m_SelectedActor)
        flags |= ImGuiTreeNodeFlags_Selected;

    if (actor->children.empty())
        flags |= ImGuiTreeNodeFlags_Leaf;

    bool open = ImGui::TreeNodeEx((void*)actor, flags, "%s", actor->Name.c_str());

    if (ImGui::IsItemClicked())
        m_SelectedActor = actor;

    if(ImGui::BeginPopupContextItem()){
        OpenContextMenu(actor);
    }

    if (open) {
        for (auto* child : actor->children)
            RenderActorNode(child);
        ImGui::TreePop();
    }
}

void Editor::DrawInspectorForActor(Actor* actor) {
    ImGui::Begin("Inspector");

    if (actor == nullptr) {
        ImGui::TextDisabled("Nenhum Actor selecionado");
        ImGui::End();
        return;
    }

    char buffer[256];
    strncpy(buffer, actor->Name.c_str(), sizeof(buffer));

    if(ImGui::InputText("##name", buffer, sizeof(buffer))){
        actor->Name = buffer;
    }

    for (auto* component : actor->GetComponents()) {
        auto meta = GetMetadata(component->GetClassName());
        if (!meta.Properties.empty()) {
            if (ImGui::CollapsingHeader(component->GetClassName().c_str(),
                                        ImGuiTreeNodeFlags_DefaultOpen))
                DrawInspector(component, meta);
        }
    }

    ImGui::End();
}

void Editor::DrawInspector(void* instance, ClassMetadata& meta) {
    auto* bytes = static_cast<uint8_t*>(instance);

    for (const auto& prop : meta.Properties) {
        void* varAddress = bytes + prop.Offset;

        switch (prop.Type) {
            case PropertyType::Float: {
                auto* v = static_cast<float*>(varAddress);
                ImGui::DragFloat(prop.Name.c_str(), v, 0.1f);
                break;
            }
            case PropertyType::Int: {
                auto* v = static_cast<int*>(varAddress);
                ImGui::DragInt(prop.Name.c_str(), v);
                break;
            }
            case PropertyType::Bool: {
                auto* v = static_cast<bool*>(varAddress);
                ImGui::Checkbox(prop.Name.c_str(), v);
                break;
            }
            case PropertyType::Vector2: {
                auto* v = static_cast<float*>(varAddress);
                ImGui::DragFloat2(prop.Name.c_str(), v, 0.1f);
                break;
            }
            case PropertyType::String: {
                auto* v = static_cast<std::string*>(varAddress);
                char buffer[256];
                strncpy(buffer, v->c_str(), sizeof(buffer));
                if (ImGui::InputText(prop.Name.c_str(), buffer, sizeof(buffer)))
                    *v = buffer;
                break;
            }
        }
    }
}

void Editor::RenderSceneView() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin("Scene");

    ImVec2 size = ImGui::GetContentRegionAvail();

    if (size.x > 0 && size.y > 0)
        m_Engine->ResizeViewport((int)size.x, (int)size.y);

    bool hovered = ImGui::IsWindowHovered();
    m_EditorCamera.ProcessInput(hovered);

    SDL_Texture* tex = m_Engine->GetViewportTexture();
    if (tex != nullptr)
        ImGui::Image((ImTextureID)tex, size);

    ImGui::End();
    ImGui::PopStyleVar();
}

void Editor::OpenContextMenu(Actor *actor) {

    if(ImGui::MenuItem("Rename")){

    }
    if (ImGui::MenuItem("Duplicate")) {

    }

    ImGui::Separator();

    if(ImGui::MenuItem("Add Child")){
        CreateActorOnScene(actor);
    }

    if (ImGui::MenuItem("Delete")) {
        if (m_SelectedActor == actor)
            m_SelectedActor = nullptr;
        m_Engine->GetScene()->RemoveActor(actor);
    }

    if(ImGui::BeginMenu("Components")){
        ImGui::EndMenu();
    }

    ImGui::EndPopup();
}

void Editor::CreateActorOnScene(Actor* parent) {
    auto scene = m_Engine->GetScene();

    auto actor = scene->CreateActor();
    actor->Name = "New Actor";
    actor->transform()->position = { 0.0f, 0.0f };

    if(parent != nullptr)
    {
        parent->AddChild(actor);
    }
}
