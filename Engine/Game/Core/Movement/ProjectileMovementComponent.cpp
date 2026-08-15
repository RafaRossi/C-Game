//
// Created by rossi on 13/07/2026.
//
#include "ProjectileMovementComponent.h"
#include "../Actor/Actor.h"

void ProjectileMovementComponent::Shoot(Vector2 direction, float speed) {
    m_Direction = direction.Normalized();
    m_Speed = speed;

    if(m_Rigidbody){
        m_Rigidbody->SetVelocity(m_Direction * m_Speed);
    }
}
