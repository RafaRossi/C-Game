//
// Created by rossi on 17/07/2026.
//
#include "Collider.h"
#include "Engine/Game/Core/Physics/PhysicsManager.h"

void Collider::OnCollisionEnter(Collider* other) {
    for (auto* component : owner->GetComponents()) {
        if(component == this) continue;
        component->OnCollisionEnter(other);
    }
}

void Collider::OnCollisionExit(Collider *other) {
    for (auto* component : owner->GetComponents()) {
        if(component == this) continue;
        component->OnCollisionExit(other);
    }
}

void Collider::OnTriggerEnter(Collider *other) {
    for (auto* component : owner->GetComponents()) {
        if(component == this) continue;
        component->OnTriggerEnter(other);
    }
}

void Collider::OnTriggerExit(Collider *other) {
    for (auto* component : owner->GetComponents()) {
        if(component == this) continue;
        component->OnTriggerExit(other);
    }
}

void Collider::Start() {
    if(!m_Rigidbody){
        m_Rigidbody = owner->GetComponent<Rigidbody>();

        if (m_Rigidbody == nullptr && owner->parent != nullptr) {
            m_Rigidbody = owner->parent->GetComponent<Rigidbody>();
        }

        if (m_Rigidbody == nullptr) {
            return;
        }
    }

    fixtureDef.isSensor = this->isTrigger;
    fixtureDef.density = this->density;
    fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

    SetCollisionLayer(collisionLayer);
}

void Collider::SetCollisionLayer(uint16 layer){
    collisionLayer = layer;

    ApplyFilter(layer, PhysicsManager::GetMaskForLayer(layer));
}

void Collider::SetFilter(uint16 category, uint16 mask) {
    ApplyFilter(category, mask);
}

void Collider::ApplyFilter(uint16 category, uint16 mask) {
    b2Filter filter;
    filter.categoryBits = category;
    filter.maskBits = mask;

    fixtureDef.filter = filter;
}
