//
// Created by rossi on 04/07/2026.
//

#ifndef SDLPROJECT_EDITORCAMERA_H
#define SDLPROJECT_EDITORCAMERA_H


#include <SDL3/SDL_render.h>
#include "../../Game/Core/Math/Vector2.h"

class EditorCamera {
public:
    Vector2 position;
    float zoom = 1.0f;

    void ProcessInput(bool isHovered);
    void Apply(SDL_Renderer* renderer) const;
    void Reset();

    Vector2 ScreenToWorld(const Vector2& screenPos) const;
    Vector2 WorldToScreen(const Vector2& worldPos) const;

private:
    bool m_IsDragging = false;
    Vector2 m_DragStart = {0.0f, 0.0f };

    Vector2 m_DragStartPos = {0.0f, 0.0f };
};


#endif //SDLPROJECT_EDITORCAMERA_H
