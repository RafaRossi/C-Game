//
// Created by rossi on 17/07/2026.
//
#include "Rigidbody.h"
#include "Engine/Game/Core/Physics/PhysicsCore.h"
#include "Engine/Game/Core/Physics/PhysicsManager.h"

void Rigidbody::SetVelocity(Vector2 velocity) {
    if(m_Body != nullptr){
        b2Vec2 b2Vel(velocity.x * PIXEL_TO_METERS, velocity.y * PIXEL_TO_METERS);
        m_Body->SetLinearVelocity(b2Vel);
    }
}

void Rigidbody::SetPosition(Vector2 newPosition) {
    if (m_Body != nullptr) {
        b2Vec2 b2Pos(newPosition.x * PIXEL_TO_METERS, newPosition.y * PIXEL_TO_METERS);
        m_Body->SetTransform(b2Pos, m_Body->GetAngle());
    }
}

void Rigidbody::Update(float deltaTime) {
    b2Vec2 box2DPos = m_Body->GetPosition();

    owner->transform()->position = { box2DPos.x * METERS_TO_PIXELS, box2DPos.y * METERS_TO_PIXELS};
}

void Rigidbody::SetRigidbodyType(RigidbodyType rigidbodyType) {
    m_RigidbodyType = rigidbodyType;

    if (m_Body != nullptr) {
        switch (m_RigidbodyType) {
            case RigidbodyType::Static:    m_Body->SetType(b2_staticBody); break;
            case RigidbodyType::Kinematic: m_Body->SetType(b2_kinematicBody); break;
            case RigidbodyType::Dynamic:   m_Body->SetType(b2_dynamicBody); break;
        }
    }
}


void Rigidbody::Start() {
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
    bodyDef.fixedRotation = freezeRotation;
    bodyDef.gravityScale = gravityScale;
    bodyDef.linearDamping = linearDamping;

    m_Body = PhysicsManager::GetWorld()->CreateBody(&bodyDef);
}
