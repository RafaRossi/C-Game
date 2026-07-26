//
// Created by rossi on 17/07/2026.
//

#include "BoxCollider.h"
#include "Engine/Game/Core/Rigidbody/Rigidbody.h"
#include "Engine/Game/Core/Physics/PhysicsCore.h"

void BoxCollider::Start() {
    if(!m_Rigidbody){
        m_Rigidbody = owner->GetComponent<Rigidbody>();

        if (m_Rigidbody == nullptr && owner->parent != nullptr) {
            m_Rigidbody = owner->parent->GetComponent<Rigidbody>();
        }

        if (m_Rigidbody == nullptr) {
            return;
        }
    }

    float halfWidth = ( m_Size.x / 2.0f ) * PIXEL_TO_METERS;
    float halfHeight = ( m_Size.y / 2.0f ) * PIXEL_TO_METERS;

    boxShape.SetAsBox(halfWidth, halfHeight);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.isSensor = this->isTrigger;

    m_Rigidbody->GetBody()->CreateFixture(&fixtureDef);
}