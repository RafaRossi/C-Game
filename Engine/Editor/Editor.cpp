#include "Editor.h"
#include "../Engine.h"  // Engine precisa do header completo aqui
#include <iostream>

void Editor::Init(SDL_Window* window, SDL_Renderer* renderer) {
    const char* basePath = SDL_GetBasePath();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    if (basePath) {
        std::string fontPath = std::string(basePath) + "Editor/Fonts/Roboto/static/Roboto-Black.ttf";

        m_FontDefault = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 18.f);
        m_FontLarge = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 22.f);

        ImFontConfig config;
        config.MergeMode = true;
        config.GlyphMinAdvanceX = 13.0f;
        static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };

        std::string iconPath = basePath ? std::string(basePath) + "Editor/Fonts/fa-solid-900.ttf" : "Editor/Fonts/fa-solid-900.ttf";
        m_FontDefault = io.Fonts->AddFontFromFileTTF(iconPath.c_str(), 14.0f, &config, icon_ranges);

    } else {
        io.Fonts->AddFontFromFileTTF("Editor/Fonts/Roboto/static/Roboto-Black.ttf", 16.f);
    }

    ImGui::StyleColorsDark();

    SetupEngineStyle();

    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);
}

void Editor::NewFrame() {
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void Editor::Render() {
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags windows_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

    const ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

    windows_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    windows_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    ImGui::Begin("MainDockSpace", nullptr, windows_flags);

    ImGui::PopStyleVar();
    ImGui::PopStyleVar(2);

    ImGuiIO& io = ImGui::GetIO();

    if(io.ConfigFlags & ImGuiConfigFlags_DockingEnable){
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    RenderMainMenuBar();

    RenderHierarchy();
    RenderSceneView();
    RenderGameView();

    DrawInspectorForActor(m_SelectedActor);

    ImGui::End();

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

    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("File")) { ImGui::EndMenu(); }

        if (ImGui::BeginMenu("Actions")) {
            if (ImGui::MenuItem("Create Actor")){
                CreateActorOnScene(nullptr);
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit")) { ImGui::EndMenu(); }

        if (ImGui::BeginMenu("Window")) { ImGui::EndMenu(); }

        ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 2.0f - 50.0f);

        if (!m_Engine->IsPlaying()) {
            if (ImGui::Button(" " ICON_FA_PLAY " Play "))
                m_Engine->Play();
        } else {
            if (ImGui::Button(" " ICON_FA_STOP " Stop "))
                m_Engine->Stop();
            ImGui::SameLine();
            if (ImGui::Button(" " ICON_FA_PAUSE " Pause "))
                m_Engine->Pause();
        }

        ImGui::EndMenuBar();
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

    bool open = ImGui::TreeNodeEx((void*)actor, flags, "%s", actor->name.c_str());

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
    ImGui::Begin("Inspector", nullptr, ImGuiWindowFlags_NoCollapse);

    if (actor == nullptr) {
        ImGui::TextDisabled("Nenhum Actor selecionado");
        ImGui::End();
        return;
    }

    char buffer[256];
    strncpy(buffer, actor->name.c_str(), sizeof(buffer));

    if(ImGui::InputText("##name", buffer, sizeof(buffer))){
        actor->name = buffer;
    }

    for (auto* component : actor->GetComponents()) {
        auto meta = GetMetadata(component->GetClassName());
        if (!meta.Properties.empty()) {
            bool isHeaderOpen = ImGui::CollapsingHeader(component->GetClassName().c_str(),ImGuiTreeNodeFlags_DefaultOpen);

            ImGui::SameLine(ImGui::GetWindowWidth() - 30);

            if(ImGui::Button("X")){
                actor->RemoveComponent(component);
            }

            if (isHeaderOpen) DrawInspector(component, meta);
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
        CreateActorOnScene(nullptr, actor);
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

Actor* Editor::CreateActorOnScene(Actor* parent) {
    auto scene = m_Engine->GetScene();

    auto actor = scene->CreateActor();
    actor->name = "New Actor";
    actor->transform()->position = { 0.0f, 0.0f };

    if(parent != nullptr)
    {
        parent->AddChild(actor);
    }

    return actor;
}

Actor* Editor::CreateActorOnScene(Actor* parent, Actor* source) {
    auto actor = CreateActorOnScene(parent);

    actor->name = source->name + " (Copy)";
    actor->layer = source->layer;

    actor->transform()->position = source->transform()->position;
    actor->transform()->rotation = source->transform()->rotation;
    actor->transform()->size = source->transform()->size;

    return actor;
}

void Editor::SetupEngineStyle() {
    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowRounding    = 4.0f;
    style.ChildRounding     = 4.0f;
    style.FrameRounding     = 3.0f;
    style.PopupRounding     = 4.0f;
    style.ScrollbarRounding = 9.0f;
    style.GrabRounding      = 3.0f;
    style.TabRounding       = 4.0f;

    ImVec4* colors = style.Colors;

    colors[ImGuiCol_WindowBg]       = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
    colors[ImGuiCol_ChildBg]        = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
    colors[ImGuiCol_PopupBg]        = ImVec4(0.10f, 0.10f, 0.10f, 0.95f);

    colors[ImGuiCol_FrameBg]        = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
    colors[ImGuiCol_FrameBgActive]  = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);

    colors[ImGuiCol_TitleBg]        = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
    colors[ImGuiCol_TitleBgActive]  = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]= ImVec4(0.11f, 0.11f, 0.11f, 1.00f);

    colors[ImGuiCol_Tab]            = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
    colors[ImGuiCol_TabHovered]     = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_TabActive]      = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_TabUnfocused]   = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);

    colors[ImGuiCol_Button]         = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_ButtonHovered]  = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_ButtonActive]   = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
    colors[ImGuiCol_Header]         = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_HeaderHovered]  = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_HeaderActive]   = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);

    colors[ImGuiCol_Separator]        = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
    colors[ImGuiCol_SeparatorActive]  = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);

    colors[ImGuiCol_DockingPreview]   = ImVec4(0.30f, 0.30f, 0.30f, 0.50f);
}
