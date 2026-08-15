//
// Created by rossi on 17/07/2026.
//

#include "BoxCollider.h"
#include "Engine/Game/Core/Rigidbody/Rigidbody.h"
#include "Engine/Game/Core/Physics/PhysicsCore.h"

void BoxCollider::Start() {
    Collider::Start();

    float halfWidth = ( m_Size.x / 2.0f ) * PIXEL_TO_METERS;
    float halfHeight = ( m_Size.y / 2.0f ) * PIXEL_TO_METERS;

    boxShape.SetAsBox(halfWidth, halfHeight);

    fixtureDef.shape = &boxShape;

    m_Rigidbody->GetBody()->CreateFixture(&fixtureDef);
}