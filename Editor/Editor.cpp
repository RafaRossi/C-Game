//
// Created by rossi on 02/07/2026.
//

#include <iostream>
#include "Editor.h"

constexpr int WINDOW_WIDTH  = 1024;
constexpr int WINDOW_HEIGHT = 768;

extern void RegisterReflection_Transform(ClassMetadata& meta);

void Editor::Init() {

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Erro SDL3: " << SDL_GetError() << std::endl;
        return;
    }

    if (!SDL_CreateWindowAndRenderer("TR Engine", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &m_Window, &m_Renderer)) {
        std::cerr << "Erro ao criar Janela/Renderer: " << SDL_GetError() << std::endl;
        return;
    }

    const char* basePath = SDL_GetBasePath();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();

    if(basePath){
        std::string fontPath = std::string(basePath) + "Editor/Fonts/Roboto/static/Roboto-Black.ttf";

        io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 16.f);
    }
    else{
        io.Fonts->AddFontFromFileTTF("Editor/Fonts/Roboto/static/Roboto-Black.ttf");
    }

    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForSDLRenderer(m_Window, m_Renderer);
    ImGui_ImplSDLRenderer3_Init(m_Renderer);

    m_IsRunning = true;
}

void Editor::NewFrame() {
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void Editor::Run() {
    while (m_IsRunning) {
        ProcessEvent();
        NewFrame();
        Render();
    }
}

void Editor::Render() {
    SDL_SetRenderDrawColor(m_Renderer, 30, 30, 30, 255);
    SDL_RenderClear(m_Renderer);

    RenderMainMenuBar();

    static Transform mockTransform = {
            .position = {100.0f, 200.0f},
            .rotation = 45.0f,
            .size     = {80.0f, 120.0f},
    };

    ClassMetadata meta = GetMetadata("Transform");

    if(!meta.Properties.empty()){
        DrawInspector(&mockTransform, meta);
    }

    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(),m_Renderer);

    SDL_RenderPresent(m_Renderer);
}

void Editor::ProcessEvent() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {

        ImGui_ImplSDL3_ProcessEvent(&event);

        if (event.type == SDL_EVENT_QUIT || event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
            m_IsRunning = false;
        }
    }
}

void Editor::Shutdown() {
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}


void Editor::RenderMainMenuBar(){
    ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImColor(30, 30, 30).Value);

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) { ImGui::EndMenu(); }
        if (ImGui::BeginMenu("Edit")) { ImGui::EndMenu(); }
        if (ImGui::BeginMenu("Window")) { ImGui::EndMenu(); }
        ImGui::EndMainMenuBar();
    }

    ImGui::PopStyleColor();
}

void Editor::DrawInspector(void *instance, ClassMetadata &meta) {
    ImGui::Begin("Inspector");
    ImGui::Text("Inspecionando: %s", meta.ClassName.c_str());
    ImGui::Separator();

    auto bytePointer = static_cast<uint8_t*>(instance);

    for (const auto& prop : meta.Properties) {
        void* varAddress = bytePointer + prop.Offset;

        switch (prop.Type) {
            case PropertyType::Float:{
                auto floatValue = static_cast<float*>(varAddress);
                ImGui::DragFloat(prop.Name.c_str(), floatValue, 0.1f);
                break;
            }
            case PropertyType::Int:{
                auto intValue = static_cast<int*>(varAddress);
                ImGui::DragInt(prop.Name.c_str(), intValue);
                break;
            }

            case PropertyType::Bool:{
                auto boolValue = static_cast<bool*>(varAddress);
                ImGui::Checkbox(prop.Name.c_str(), boolValue);
                break;
            }

            case PropertyType::Vector2:{
                auto floatValue = static_cast<float*>(varAddress);
                ImGui::DragFloat2(prop.Name.c_str(), floatValue, 0.1f);
                break;
            }

            case PropertyType::String:{
                auto strValue = static_cast<std::string*>(varAddress);

                char buffer[256];

                strncpy(buffer, strValue->c_str(), sizeof(buffer));

                if(ImGui::InputText(prop.Name.c_str(), buffer, sizeof(buffer))){
                    *strValue = buffer;
                }

                break;
            }
        }
    }
    ImGui::End();
}
