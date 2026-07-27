//
// Created by rossi on 17/07/2026.
//
#include "Collider.h"


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

}
