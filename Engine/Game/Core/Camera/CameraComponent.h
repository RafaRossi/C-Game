//
// Created by rossi on 30/06/2026.
//

#ifndef SDLPROJECT_CAMERACOMPONENT_H
#define SDLPROJECT_CAMERACOMPONENT_H


#include "../Actor/Actor.h"
#include "../Component/Component.h"
#include "ClearFlags.h"
#include "Engine/Game/Core/Color/Color.h"
#include "Engine/Game/Core/Camera/Follow/FollowStrategy.h"

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
    PROPERTY() float zoom = 2.0f;
    PROPERTY() Color backgroundColor = { 20, 30, 45, 255 };

    ClearFlags clearFlags = ClearFlags::SolidColor;
    int cullingMask = ~0;

    PROPERTY() bool         followTarget = true;
    PROPERTY() Transform*   target       = nullptr;

    CameraDeadZone deadZone;
    CameraBounds   bounds;

    void LateUpdate(float deltaTime) override;
    void Apply(SDL_Renderer* renderer);
    void RenderBackground(SDL_Renderer* renderer);

    Vector2 WorldToScreen(Vector2 worldPos);
    Vector2 ScreenToWorld(Vector2 screenPos);

    bool IsUnique() const override { return true; }

    bool IsMainCamera() const { return m_IsMainCamera; }
    void SetMainCamera(bool value) { m_IsMainCamera = value; }

    template<typename T, typename... Args>
    T* SetFollowMode(Args&&... args){
        delete m_FollowStrategy;
        auto* strategy = new T(std::forward<Args>(args)...);
        m_FollowStrategy = strategy;
        return strategy;
    }

private:
    PROPERTY() bool m_IsMainCamera = false;

    FollowStrategy* m_FollowStrategy = nullptr;
};


#endif //SDLPROJECT_CAMERACOMPONENT_H
