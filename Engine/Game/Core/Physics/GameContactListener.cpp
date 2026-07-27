//
// Created by rossi on 26/07/2026.
//

#include "GameContactListener.h"
#include "Engine/Game/Core/Collision/Collider.h"

void GameContactListener::BeginContact(b2Contact *contact) {
    auto* colliderA = reinterpret_cast<Collider*>(contact->GetFixtureA()->GetUserData().pointer);
    auto* colliderB = reinterpret_cast<Collider*>(contact->GetFixtureB()->GetUserData().pointer);

    if (!colliderA || !colliderB) return;

    bool isSensor = contact->GetFixtureA()->IsSensor() ||
                    contact->GetFixtureB()->IsSensor();

    if (isSensor) {
        colliderA->OnTriggerEnter(colliderB);
        colliderB->OnTriggerEnter(colliderA);
    } else {
        colliderA->OnCollisionEnter(colliderB);
        colliderB->OnCollisionEnter(colliderA);
    }
}

void GameContactListener::EndContact(b2Contact *contact) {
    auto* colliderA = reinterpret_cast<Collider*>(contact->GetFixtureA()->GetUserData().pointer);
    auto* colliderB = reinterpret_cast<Collider*>(contact->GetFixtureB()->GetUserData().pointer);

    if (!colliderA || !colliderB) return;

    bool isSensor = contact->GetFixtureA()->IsSensor() ||
                    contact->GetFixtureB()->IsSensor();

    if (isSensor) {
        colliderA->OnTriggerExit(colliderB);
        colliderB->OnTriggerExit(colliderA);
    } else {
        colliderA->OnCollisionExit(colliderB);
        colliderB->OnCollisionExit(colliderA);
    }
}
