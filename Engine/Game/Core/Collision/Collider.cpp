//
// Created by rossi on 17/07/2026.
//

#include "Collider.h"
#include "Engine/Game/Core/Rigidbody/Rigidbody.h"
#include "Engine/Game/Core/Physics/PhysicsCore.h"

BoxCollider::BoxCollider() {
    m_Rigidbody = owner->GetComponent<Rigidbody>();

    if(m_Rigidbody == nullptr) return;

    float halfWidth = ( size.x / 2.0f ) * PIXEL_TO_METERS;
    float halfHeight = ( size.y / 2.0f ) * PIXEL_TO_METERS;

    boxShape.SetAsBox(halfWidth, halfHeight);

    m_Rigidbody->SetShape(&boxShape);
}
