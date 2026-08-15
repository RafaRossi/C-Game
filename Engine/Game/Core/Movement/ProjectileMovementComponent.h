//
// Created by rossi on 13/07/2026.
//

#ifndef SDLPROJECT_PROJECTILEMOVEMENTCOMPONENT_H
#define SDLPROJECT_PROJECTILEMOVEMENTCOMPONENT_H

#include "Engine/Game/Core/Component/Component.h"
#include "Engine/Game/Core/Math/Vector2.h"
#include "Engine/Game/Core/Rigidbody/Rigidbody.h"

class ProjectileMovementComponent : public Component{
    REGISTER_BODY(ProjectileMovementComponent, Component)

public:
    ProjectileMovementComponent() = default;

    explicit ProjectileMovementComponent(Actor* owner, Rigidbody* rigidbody) : Component(owner) {
        m_Rigidbody = rigidbody;
    }

    ~ProjectileMovementComponent() override = default;

    void Shoot(Vector2 direction, float speed);

private:
    Rigidbody* m_Rigidbody{};

    PROPERTY() Vector2 m_Direction = Vector2::Zero;
    PROPERTY() float m_Speed = 500.0f;
};

#endif //SDLPROJECT_PROJECTILEMOVEMENTCOMPONENT_H
