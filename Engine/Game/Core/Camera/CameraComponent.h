//
// Created by rossi on 30/06/2026.
//

#ifndef SDLPROJECT_CAMERACOMPONENT_H
#define SDLPROJECT_CAMERACOMPONENT_H


#include "../Actor/Actor.h"
#include "../Component/Component.h"
#include "ClearFlags.h"
#include "Engine/Game/Core/Color/Color.h"

struct CameraDeadZone {
    float width  = 0.0f;
    float height = 0.0f;
};

struct CameraBounds{
    bool    enabled = false;
    Vector2 min     = {0.0f, 0.0f};
    Vector2 max     = {0.0f, 0.0f};
};

class CameraComponent : public Component {
    REGISTER_BODY(CameraComponent, Component)
public:
    PROPERTY() float zoom = 1.0f;
    PROPERTY() Color backgroundColor = { 20, 30, 45, 255 };

    ClearFlags clearFlags = ClearFlags::SolidColor;
    int cullingMask = ~0;

    PROPERTY() bool         followTarget = true;
    PROPERTY() Transform*   target       = nullptr;
    PROPERTY() float        smoothSpeed  = 5.0f;

    CameraDeadZone deadZone;
    CameraBounds   bounds;

    void Update(float deltaTime) override;

    void Apply(SDL_Renderer* renderer);
    void RenderBackground(SDL_Renderer* renderer);

    Vector2 WorldToScreen(const Vector2& worldPos) const {
        return (worldPos - owner->GetWorldPosition()) * zoom;
    }

    Vector2 ScreenToWorld(const Vector2& screenPos) const {
        return screenPos / zoom + owner->GetWorldPosition();
    }

    bool IsUnique() const override { return true; }

    bool IsMainCamera() const { return m_IsMainCamera; }
    void SetMainCamera(bool value) { m_IsMainCamera = value; }

private:
    PROPERTY() bool m_IsMainCamera = false;

    Vector2 m_CurrentVelocity = { 0.0f, 0.0f};
};


#endif //SDLPROJECT_CAMERACOMPONENT_H
