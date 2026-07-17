//
// Created by rossi on 17/07/2026.
//

#ifndef SDLPROJECT_RIGIDBODY_H
#define SDLPROJECT_RIGIDBODY_H

#include "Engine/Game/Core/Component/Component.h"
#include "box2d/box2d.h"
#include "Engine/Game/Core/Math/Vector2.h"
#include "Engine/Game/Core/Actor/Actor.h"

enum class RigidbodyType
{
    Dynamic,
    Kinematic,
    Static
};

class Rigidbody : public Component{
    REGISTER_BODY(Rigidbody, Component)

private:
    b2Body* m_Body = nullptr;
    RigidbodyType m_RigidbodyType = RigidbodyType::Dynamic;

public:
    Rigidbody();

    void Update(float deltaTime) override;

    void SetRigidbodyType(RigidbodyType rigidbodyType);

    RigidbodyType GetRigidbodyType() { return  m_RigidbodyType; }

    void SetVelocity(Vector2 velocity);
    void SetPosition(Vector2 newPosition);

    void SetShape(b2Shape* shape);

    PROPERTY() bool freezeRotation = true;
    PROPERTY() float density = 1.f;
};

#endif //SDLPROJECT_RIGIDBODY_H
