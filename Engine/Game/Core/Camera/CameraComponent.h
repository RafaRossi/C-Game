//
// Created by rossi on 30/06/2026.
//

#ifndef SDLPROJECT_CAMERACOMPONENT_H
#define SDLPROJECT_CAMERACOMPONENT_H


#include "../Actor/Actor.h"
#include "../Component/Component.h"
#include "ClearFlags.h"

class CameraComponent : public Component {
public:
    float zoom = 1.0f;
    SDL_Color backgroundColor = { 20, 30, 45, 255 };

    ClearFlags clearFlags = ClearFlags::SolidColor;
    int cullingMask = ~0;

    Vector2 WorldToScreen(const Vector2& worldPos) const {
        return (worldPos - owner->GetWorldPosition()) * zoom;
    }

    Vector2 ScreenToWorld(const Vector2& screenPos) const {
        return screenPos / zoom + owner->GetWorldPosition();
    }

    void RenderBackground(SDL_Renderer* renderer);

    void Apply(SDL_Renderer* renderer);

    std::string GetClassName() const override { return "CameraComponent"; }

    Component* Clone() const override;

};


#endif //SDLPROJECT_CAMERACOMPONENT_H
