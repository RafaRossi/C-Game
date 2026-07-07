//
// Created by rossi on 04/07/2026.
//

#include "EditorCamera.h"
#include "imgui.h"

void EditorCamera::ProcessInput(bool isHovered) {
    if(!isHovered) return;

    ImGuiIO& io = ImGui::GetIO();

    if(io.MouseWheel != 0.0f){
        float zoomDelta = io.MouseWheel * 0.01f * zoom;
        zoom = std::max(0.1f, zoom + zoomDelta);
    }

    if(ImGui::IsMouseDown(ImGuiMouseButton_Middle)){
        if(!m_IsDragging){
            m_IsDragging = true;
            m_DragStart = {io.MousePos.x, io.MousePos.y};
            m_DragStartPos = position;
        }

        Vector2 current = {io.MousePos.x, io.MousePos.y};
        Vector2 delta = (current - m_DragStart) * (1.0f / zoom);
        position = m_DragStartPos - delta;
    }else{
        m_IsDragging = false;
    }
}

void EditorCamera::Apply(SDL_Renderer *renderer) const {
    int w, h;

    SDL_GetCurrentRenderOutputSize(renderer, &w, &h);

    SDL_SetRenderScale(renderer, zoom, zoom);

    SDL_FPoint offset = { -position.x * zoom, -position.y * zoom};
    SDL_Rect viewport = {
            (int)offset.x,
            (int)offset.y,
            (int)(w/zoom),
            (int)(h/zoom)
    };

    SDL_SetRenderViewport(renderer, &viewport);
}

void EditorCamera::Reset() {
    position = {0.0f, 0.0f};
    zoom = 1.0f;
}

Vector2 EditorCamera::ScreenToWorld(const Vector2 &screenPos) const {
    Vector2 worldPos;
    worldPos.x = ((screenPos.x - (viewportSize.x * 0.5f)) / zoom) + position.x;
    worldPos.y = ((screenPos.y - (viewportSize.y * 0.5f)) / zoom) + position.y;
    return worldPos;
}

Vector2 EditorCamera::WorldToScreen(const Vector2 &worldPos) const {
    Vector2 screenPos;
    screenPos.x = ((worldPos.x - position.x) * zoom) + (viewportSize.x * 0.5f);
    screenPos.y = ((worldPos.y - position.y) * zoom) + (viewportSize.y * 0.5f);
    return screenPos;
}

void EditorCamera::SetViewportSize(float width, float height) {
    viewportSize = {width, height};
}
