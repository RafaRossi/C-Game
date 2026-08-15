//
// Created by rossi on 17/07/2026.
//

#ifndef SDLPROJECT_RIGIDBODY_H
#define SDLPROJECT_RIGIDBODY_H

#include "Engine/Game/Core/Component/Component.h"
#include "box2d/box2d.h"
#include "Engine/Game/Core/Math/Vector2.h"
#include "Engine/Game/Core/Actor/Actor.h"
#include "Engine/Game/Core/Physics/PhysicsManager.h"
#include "Engine/Game/Core/Physics/PhysicsCore.h"

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
    RigidbodyType m_RigidbodyType = RigidbodyType::Static;

    PROPERTY() bool m_FreezeRotation = true;
    PROPERTY() float m_Density = 1.f;
    PROPERTY() float m_GravityScale = 0.f;
    PROPERTY() float m_LinearDamping = 10.f;

public:
    Rigidbody() = default;

    explicit Rigidbody(Actor* owner, RigidbodyType rigidbodyType) : Component(owner), m_RigidbodyType(rigidbodyType) {
        b2BodyDef bodyDef;

        switch (m_RigidbodyType) {

            case RigidbodyType::Dynamic:
                bodyDef.type = b2_dynamicBody;
                break;
            case RigidbodyType::Kinematic:
                bodyDef.type = b2_kinematicBody;
                break;
            case RigidbodyType::Static:
                bodyDef.type = b2_staticBody;
                break;
        }

        Vector2 pos = owner->GetWorldPosition();
        bodyDef.position.Set(pos.x * PIXEL_TO_METERS, pos.y * PIXEL_TO_METERS);
        bodyDef.fixedRotation = m_FreezeRotation;
        bodyDef.gravityScale = m_GravityScale;
        bodyDef.linearDamping = m_LinearDamping;

        m_Body = PhysicsManager::GetWorld()->CreateBody(&bodyDef);
    }

    ~Rigidbody() override;

    void Start() override;

    void Update(float deltaTime) override;

    void SetRigidbodyType(RigidbodyType rigidbodyType);

    RigidbodyType GetRigidbodyType() { return  m_RigidbodyType; }

    void SetVelocity(Vector2 velocity);
    void SetPosition(Vector2 newPosition);

    b2Body* GetBody() { return m_Body; }

    float GetLinearDamping() const { return m_Body->GetLinearDamping(); }
    void SetLinearDamping(float value) { m_Body->SetLinearDamping(value); }

    float GetGravityScale() const { return m_Body->GetGravityScale(); }
    void SetGravityScale(float value) { m_Body->SetGravityScale(value); }

    bool IsFixedRotation() const { return m_Body->IsFixedRotation(); }
    void SetIsFixedRotation(bool value) { m_Body->SetFixedRotation(value); }
};

#endif //SDLPROJECT_RIGIDBODY_H
