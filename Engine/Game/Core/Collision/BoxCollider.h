//
// Created by rossi on 17/07/2026.
//

#ifndef SDLPROJECT_BOXCOLLIDER_H
#define SDLPROJECT_BOXCOLLIDER_H


#include "Collider.h"
#include "CollisionMask.h"

class BoxCollider : public Collider {
    REGISTER_BODY(BoxCollider, Collider)

public:
    BoxCollider() = default;

    explicit BoxCollider(Actor* owner, Rigidbody* rigidbody, Vector2 size, bool isSensor = false, uint16 collisionLayer = CollisionLayer::Default) : Collider(owner, rigidbody, isSensor, collisionLayer), m_Size(size) {};
    ~BoxCollider() override = default;

    void Start() override;

private:
    b2PolygonShape boxShape;

    PROPERTY() Vector2 m_Size = { 100.f, 100.f };
};

#endif //SDLPROJECT_BOXCOLLIDER_H
