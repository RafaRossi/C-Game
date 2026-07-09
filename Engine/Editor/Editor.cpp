#include "Editor.h"
#include "../Engine.h"
#include "PropertyType/PropertyType.h"
#include "Engine/Editor/ComponentFactory/ComponentFactory.h"
#include "Engine/Editor/SceneSerializer/SceneSerializer.h"
#include "Engine/ThirdParty/portable-file-dialogs.h"
#include <iostream>
#include <filesystem>

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

    HandleShortcuts();

    RenderMainMenuBar();

    RenderHierarchy();
    RenderSceneView();
    RenderGameView();

    RenderContentBrowser();

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
        if (ImGui::BeginMenu("File")) {
            std::vector<std::string> sceneFilter = { "Cenas da Engine (*.tscene)", "*.tscene" };

            if (ImGui::MenuItem("New Scene", "Ctrl+N")){
                CreateNewScene();
                m_CurrentScenePath = "";
            }
            if (ImGui::MenuItem("Save Scene", "Ctrl+S")) {
                if(m_CurrentScenePath.empty()){
                    std::string filePath = SaveFileDialog("Salvar Nova Cena", sceneFilter);

                    if (!filePath.empty()) {
                        m_CurrentScenePath = filePath;
                        SceneSerializer::SaveScene(m_Engine->GetScene(), m_CurrentScenePath);
                    }else{
                        SceneSerializer::SaveScene(m_Engine->GetScene(), m_CurrentScenePath);
                    }
                }
            }

            if (ImGui::MenuItem("Save As...")) {
                std::string filepath = SaveFileDialog("Salvar Cena Como...", sceneFilter);
                if (!filepath.empty()) {
                    m_CurrentScenePath = filepath;
                    SceneSerializer::SaveScene(m_Engine->GetScene(), m_CurrentScenePath);
                }
            }
            if (ImGui::MenuItem("Load Scene", "Ctrl+O")) {
                std::string filepath = OpenFileDialog("Abrir Cena do Jogo", sceneFilter);

                if (!filepath.empty()) {
                    SceneAsset asset;
                    asset.filePath = filepath;

                    m_Engine->ChangeScene(asset.Instantiate());
                    m_CurrentScenePath = filepath;
                }
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit")) { ImGui::EndMenu(); }

        if (ImGui::BeginMenu("Actions")) {
            if (ImGui::MenuItem("Create Actor")){
                CreateNewActorOnScene(nullptr);
            }
            ImGui::EndMenu();
        }

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
        ImGui::TextDisabled("No Selected Actor");
        ImGui::End();
        return;
    }

    char buffer[256];
    strncpy(buffer, actor->name.c_str(), sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    if(ImGui::InputText("##name", buffer, sizeof(buffer))){
        actor->name = buffer;
    }

    for (auto* component : actor->GetComponents()) {
        FieldCollector collector;
        component->AutoExposeField(collector);

        const auto& fields = collector.GetFields();

        ImGui::PushID(component);

        ImGui::SetNextItemAllowOverlap();
        bool isHeaderOpen = ImGui::CollapsingHeader(component->GetComponentName().c_str(), ImGuiTreeNodeFlags_DefaultOpen);

        if(component->CanBeRemoved()){
            ImGui::SameLine(ImGui::GetWindowWidth() - 30);
            if(ImGui::Button("X")){
                actor->RemoveComponent(component);

                ImGui::PopID();
                break;
            }
        }

        if (isHeaderOpen) {
            if (!fields.empty()) {
                DrawInspector(fields);
            } else {
                ImGui::TextDisabled("No exposed properties.");
            }
        }

        ImGui::PopID();
    }

    ImGui::End();
}

void Editor::DrawInspector(const std::vector<ExposedField>& fields) {
    for (const auto& field : fields) {
        switch (field.Type) {
            case PropertyType::Float: {
                ImGui::DragFloat(field.Name.c_str(), static_cast<float*>(field.Ptr), 0.1f);
                break;
            }
            case PropertyType::Int: {
                ImGui::DragInt(field.Name.c_str(), static_cast<int*>(field.Ptr));
                break;
            }
            case PropertyType::Bool: {
                ImGui::Checkbox(field.Name.c_str(), static_cast<bool*>(field.Ptr));
                break;
            }
            case PropertyType::Vector2: {
                ImGui::DragFloat2(field.Name.c_str(), reinterpret_cast<float*>(field.Ptr), 0.1f);
                break;
            }
            case PropertyType::String: {
                auto* v = static_cast<std::string*>(field.Ptr);
                char buffer[256];
                strncpy(buffer, v->c_str(), sizeof(buffer));
                if (ImGui::InputText(field.Name.c_str(), buffer, sizeof(buffer)))
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

    if (size.x > 0 && size.y > 0){
        m_Engine->ResizeViewport((int)size.x, (int)size.y);
        m_EditorCamera.SetViewportSize(size.x, size.y);
    }

    bool hovered = ImGui::IsWindowHovered();
    m_EditorCamera.ProcessInput(hovered);

    SDL_Texture* tex = m_Engine->GetViewportTexture();
    if (tex != nullptr)
    {
        ImGui::Image((ImTextureID)tex, size);
        ImVec2 imageOrigin = ImGui::GetItemRectMin();

        DrawGrid({imageOrigin.x, imageOrigin.y}, {size.x, size.y} );
        DrawGizmo(m_SelectedActor, { imageOrigin.x, imageOrigin.y });
    }

    ImGui::End();
    ImGui::PopStyleVar();
}

void Editor::OpenContextMenu(Actor *actor) {

    if(ImGui::MenuItem("Rename")){

    }
    if (ImGui::MenuItem("Duplicate")) {
        m_SelectedActor = DuplicateActorOnScene(m_SelectedActor->parent, actor);
    }

    ImGui::Separator();

    if(ImGui::MenuItem("Add Child")){
        m_SelectedActor = CreateNewActorOnScene(actor);
    }

    if (ImGui::MenuItem("Delete")) {
        if (m_SelectedActor == actor)
            m_SelectedActor = nullptr;
        m_Engine->GetScene()->RemoveActor(actor);
    }

    if(ImGui::BeginMenu("Components")){

        for(const auto& [compName, creatorFunc] : ComponentFactory::GetRegistry()){
            if(ImGui::MenuItem(compName.c_str())){
                Component* newComp = ComponentFactory::Create(compName);

                if(newComp){
                    actor->AddComponent(newComp);
                }
            }
        }

        ImGui::EndMenu();
    }

    ImGui::EndPopup();
}

Actor* Editor::CreateNewActorOnScene(Actor* parent) {
    auto scene = m_Engine->GetScene();

    auto actor = scene->CreateActor();
    actor->name = GetUniqueNameInHierarchy(parent, actor->name);

    actor->transform()->position = { 0.0f, 0.0f };

    if(parent != nullptr)
    {
        parent->AddChild(actor);
    }

    return actor;
}

Actor* Editor::DuplicateActorOnScene(Actor* parent, Actor* source) {
    auto actor = CreateNewActorOnScene(parent);
    actor->layer = source->layer;

    actor->transform()->position = source->transform()->position;
    actor->transform()->rotation = source->transform()->rotation;
    actor->transform()->size = source->transform()->size;

    for (auto* component : source->GetComponents()) {
        if (component->GetComponentName() == "Transform") continue;

        auto* newComponent = ComponentFactory::Create(component->GetComponentName());

        if(newComponent){
            actor->AddComponent(newComponent);

            FieldCollector sourceCollector;
            component->AutoExposeField(sourceCollector);

            FieldCollector destCollector;
            newComponent->AutoExposeField(destCollector);

            const auto& sourceFields = sourceCollector.GetFields();
            const auto& destFields = destCollector.GetFields();

            for (size_t i = 0; i < sourceFields.size(); ++i) {
                if (sourceFields[i].Type == destFields[i].Type) {
                    switch (sourceFields[i].Type) {
                        case PropertyType::Float:
                            *(float*)destFields[i].Ptr = *(float*)sourceFields[i].Ptr;
                            break;
                        case PropertyType::Int:
                            *(int*)destFields[i].Ptr = *(int*)sourceFields[i].Ptr;
                            break;
                        case PropertyType::Bool:
                            *(bool*)destFields[i].Ptr = *(bool*)sourceFields[i].Ptr;
                            break;
                        case PropertyType::Vector2:
                            *(Vector2*)destFields[i].Ptr = *(Vector2*)sourceFields[i].Ptr;
                            break;
                        case PropertyType::String:
                            *(std::string*)destFields[i].Ptr = *(std::string*)sourceFields[i].Ptr;
                            break;
                    }
                }
            }
        }
    }

    for (auto* child : source->children) {
        DuplicateActorOnScene(actor, child);
    }

    return actor;
}

std::string Editor::GetUniqueNameInHierarchy(Actor* parent, const std::string& baseName) {
    auto scene = m_Engine->GetScene();
    std::vector<Actor*> siblings;

    if (parent != nullptr) {
        siblings = parent->children;
    } else {
        for (auto* actor : scene->GetActors()) {
            if (actor->parent == nullptr) {
                siblings.push_back(actor);
            }
        }
    }

    std::string candidateName = baseName;
    bool nameExists = true;
    int counter = 1;

    while (nameExists) {
        nameExists = false;
        for (auto* sibling : siblings) {
            if (sibling->name == candidateName) {
                nameExists = true;
                break;
            }
        }

        if (nameExists) {
            candidateName = baseName + " (" + std::to_string(counter) + ")";
            counter++;
        }
    }

    return candidateName;
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

void Editor::DrawGrid(Vector2 imageOrigin, Vector2 size) {
    ImDrawList* drawList = ImGui::GetWindowDrawList();

    float gridSize = 50.0f;

    ImU32 thinColor = IM_COL32(255, 255, 255, 15);
    ImU32 thickColor = IM_COL32(255, 255, 255, 50);

    Vector2 minWorld = m_EditorCamera.ScreenToWorld({ 0.0f, 0.0f });
    Vector2 maxWorld = m_EditorCamera.ScreenToWorld( { size.x, size.y });

    for (float x = std::floor(minWorld.x / gridSize) * gridSize; x <= maxWorld.x; x += gridSize) {
        Vector2 screenPos = m_EditorCamera.WorldToScreen({x, 0.0f});
        float lineX = imageOrigin.x + screenPos.x;
        ImU32 col = (std::abs(x) < 0.1f) ? thickColor : thinColor;
        drawList->AddLine({lineX, imageOrigin.y}, {lineX, imageOrigin.y + size.y}, col, (std::abs(x) < 0.1f) ? 2.0f : 1.0f);
    }

    for (float y = std::floor(minWorld.y / gridSize) * gridSize; y <= maxWorld.y; y += gridSize) {
        Vector2 screenPos = m_EditorCamera.WorldToScreen({0.0f, y});
        float lineY = imageOrigin.y + screenPos.y;
        ImU32 col = (std::abs(y) < 0.1f) ? thickColor : thinColor;
        drawList->AddLine({imageOrigin.x, lineY}, {imageOrigin.x + size.x, lineY}, col, (std::abs(y) < 0.1f) ? 2.0f : 1.0f);
    }
}

void Editor::DrawGizmo(Actor* actor, Vector2 imageOrigin) {
    if (actor == nullptr) return;

    ImDrawList* drawList = ImGui::GetWindowDrawList();
    ImGuiIO& io = ImGui::GetIO();

    Vector2 worldPos  = actor->GetWorldPosition();
    Vector2 screenPos = m_EditorCamera.WorldToScreen(worldPos);
    ImVec2 origin = { imageOrigin.x + screenPos.x, imageOrigin.y + screenPos.y };

    const float axisLength   = 82.0f;
    const float arrowSize    = 20.0f;
    const float hitThreshold = 20.0f;
    const float rectSize     = 22.0f;

    ImVec2 xEnd = { origin.x + axisLength, origin.y };
    ImVec2 yEnd = { origin.x, origin.y + axisLength };

    ImU32 colorX      = IM_COL32(220, 60, 60, 255);
    ImU32 colorY      = IM_COL32(60, 220, 90, 255);
    ImU32 colorBoth   = IM_COL32(60, 160, 220, 255);
    ImU32 colorXHover = IM_COL32(255, 120, 120, 255);
    ImU32 colorYHover = IM_COL32(120, 255, 150, 255);
    ImU32 colorBothHover = IM_COL32(120, 200, 255, 255);

    ImVec2 mouse = io.MousePos;

    auto distToSegment = [](ImVec2 p, ImVec2 a, ImVec2 b) -> float {
        ImVec2 ab = { b.x - a.x, b.y - a.y };
        ImVec2 ap = { p.x - a.x, p.y - a.y };
        float lenSq = ab.x * ab.x + ab.y * ab.y;
        float t = lenSq > 0.0f ? (ap.x * ab.x + ap.y * ab.y) / lenSq : 0.0f;
        t = std::clamp(t, 0.0f, 1.0f);
        ImVec2 closest = { a.x + ab.x * t, a.y + ab.y * t };
        float dx = p.x - closest.x;
        float dy = p.y - closest.y;
        return std::sqrt(dx * dx + dy * dy);
    };

    bool hoverBoth = mouse.x >= origin.x && mouse.x <= origin.x + rectSize &&
                     mouse.y >= origin.y && mouse.y <= origin.y + rectSize;

    bool hoverX = !hoverBoth && distToSegment(mouse, origin, xEnd) <= hitThreshold;
    bool hoverY = !hoverBoth && distToSegment(mouse, origin, yEnd) <= hitThreshold;

    if (m_GizmoDraggingAxis == -1) {
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
            if (hoverBoth) m_GizmoDraggingAxis = 2; // Eixo 2 = Ambos
            else if (hoverX) m_GizmoDraggingAxis = 0;
            else if (hoverY) m_GizmoDraggingAxis = 1;

            if (m_GizmoDraggingAxis != -1) {
                m_GizmoDraggingStartMouse = { mouse.x, mouse.y };
                m_GizmoDragStartPos   = actor->transform()->position;
            }
        }
    } else {
        if (ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
            Vector2 deltaScreen = { mouse.x - m_GizmoDraggingStartMouse.x, mouse.y - m_GizmoDraggingStartMouse.y };
            Vector2 deltaWorld  = deltaScreen * (1.0f / m_EditorCamera.zoom);

            Vector2 newPos = m_GizmoDragStartPos;

            if (m_GizmoDraggingAxis == 0) {
                newPos.x = m_GizmoDragStartPos.x + deltaWorld.x;
            } else if (m_GizmoDraggingAxis == 1) {
                newPos.y = m_GizmoDragStartPos.y + deltaWorld.y;
            } else if (m_GizmoDraggingAxis == 2) {
                newPos.x = m_GizmoDragStartPos.x + deltaWorld.x;
                newPos.y = m_GizmoDragStartPos.y + deltaWorld.y;
            }

            actor->transform()->position = newPos;
        } else {
            m_GizmoDraggingAxis = -1;
        }
    }

    bool draggingX = m_GizmoDraggingAxis == 0;
    bool draggingY = m_GizmoDraggingAxis == 1;
    bool draggingBoth = m_GizmoDraggingAxis == 2;

    drawList->AddLine(origin, xEnd, (hoverX || draggingX) ? colorXHover : colorX, 3.0f);
    drawList->AddLine(origin, yEnd, (hoverY || draggingY) ? colorYHover : colorY, 3.0f);

    drawList->AddTriangleFilled(
            { xEnd.x, xEnd.y - arrowSize * 0.5f },
            { xEnd.x, xEnd.y + arrowSize * 0.5f },
            { xEnd.x + arrowSize, xEnd.y },
            (hoverX || draggingX) ? colorXHover : colorX
    );

    drawList->AddTriangleFilled(
            { yEnd.x - arrowSize * 0.5f, yEnd.y },
            { yEnd.x + arrowSize * 0.5f, yEnd.y },
            { yEnd.x, yEnd.y + arrowSize },
            (hoverY || draggingY) ? colorYHover : colorY
    );

    drawList->AddCircleFilled(origin, 4.0f, IM_COL32(230, 230, 230, 255));

    ImU32 rectColor = (hoverBoth || draggingBoth) ? colorBothHover : colorBoth;
    drawList->AddRectFilled(origin, {origin.x + rectSize, origin.y + rectSize}, rectColor);
}

void Editor::HandleShortcuts() {
    ImGuiIO& io = ImGui::GetIO();

    if(io.WantTextInput) return;

    if(io.KeyCtrl && ImGui::IsKeyPressed(ImGuiKey_D)){
        if(m_SelectedActor != nullptr){
            m_SelectedActor = DuplicateActorOnScene(m_SelectedActor->parent, m_SelectedActor);
        }
    }

    if (io.KeyCtrl && ImGui::IsKeyPressed(ImGuiKey_S)) {
        std::string scenePath = std::string(PROJECT_SOURCE_DIR) + "/Scenes/Test.tscene";
        SceneSerializer::SaveScene(m_Engine->GetScene(), scenePath);
    }

    if (ImGui::IsKeyPressed(ImGuiKey_Delete)) {
        if (m_SelectedActor != nullptr) {
            m_Engine->GetScene()->RemoveActor(m_SelectedActor);
            m_SelectedActor = nullptr;
        }
    }
}

void Editor::RenderContentBrowser() {
    ImGui::Begin("Content Browser");

    std::string assetsPath = std::string(PROJECT_SOURCE_DIR) + "/Sandbox";
    assetsPath.erase(std::remove(assetsPath.begin(), assetsPath.end(), '\"'), assetsPath.end());

    if (!std::filesystem::exists(assetsPath)) {
        std::filesystem::create_directories(assetsPath);
    }

    DrawDirectoryNodes(assetsPath);

    ImGui::End();
}

void Editor::CreateNewScene() {
    m_SelectedActor = nullptr;
    m_CopiedActor = nullptr;

    auto* newScene = new Scene();
    auto* actorCamera = newScene->CreateActor("Main Camera");

    newScene->SetMainCamera(actorCamera->AddComponent<CameraComponent>());

    m_Engine->ChangeScene(newScene);
    m_CurrentScenePath = "";
}

std::string Editor::OpenFileDialog(const std::string& title, const std::vector<std::string>& filters) {
    std::string defaultPath = std::string(PROJECT_SOURCE_DIR) + "/Sandbox/";
    auto dialog = pfd::open_file(title, ".", filters);
    auto selection = dialog.result();

    if (!selection.empty()) {
        return selection[0];
    }

    return "";
}

std::string Editor::SaveFileDialog(const std::string& title, const std::vector<std::string>& filters) {
    std::string defaultPath = std::string(PROJECT_SOURCE_DIR) + "/Sandbox/";
    std::filesystem::create_directories(defaultPath);

    auto dialog = pfd::save_file(title, defaultPath, filters);
    std::string destination = dialog.result();

    if(!destination.empty()){
        if(destination.find(".tscene") == std::string::npos){
            destination += ".tscene";
        }
    }

    return destination;
}

void Editor::DrawDirectoryNodes(const std::filesystem::path& directoryPath) {
    for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
        const auto& path = entry.path();
        auto filename = path.filename().string();

        if (entry.is_directory()) {
            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;

            bool isOpen = ImGui::TreeNodeEx(filename.c_str(), flags);
            if (isOpen) {
                DrawDirectoryNodes(path);
                ImGui::TreePop();
            }
        } else {
            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_SpanAvailWidth;

            ImGui::TreeNodeEx(filename.c_str(), flags);

            if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
                if (path.extension() == ".tscene") {
                    SceneAsset asset;
                    asset.filePath = path.string();

                    m_SelectedActor = nullptr;
                    m_CopiedActor = nullptr;

                    m_Engine->ChangeScene(asset.Instantiate());
                    m_CurrentScenePath = path.string();
                    std::cout << "[Editor] Cena carregada pelo Browser: " << filename << "\n";
                }
            }
        }
    }
}

