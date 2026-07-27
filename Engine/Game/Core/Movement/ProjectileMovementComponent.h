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

    PROPERTY() Vector2 direction = {1.0f, 0.0f};
    PROPERTY() float speed = 500.0f;

    void Update(float deltaTime) override;

    void Shoot(Vector2 direction, float speed)
    {
        this->direction = direction.Normalized();
        this->speed = speed;
    }

private:
    Rigidbody* m_Rigidbody{};
};

#endif //SDLPROJECT_PROJECTILEMOVEMENTCOMPONENT_H
