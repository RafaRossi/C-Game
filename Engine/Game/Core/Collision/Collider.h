//
// Created by rossi on 17/07/2026.
//
#pragma once
#ifndef SDLPROJECT_COLLIDER_H
#define SDLPROJECT_COLLIDER_H


#include "Engine/Game/Core/Component/Component.h"
#include "Engine/Game/Core/Math/Vector2.h"
#include "Engine/Game/Core/Rigidbody/Rigidbody.h"
#include "CollisionMask.h"

class Collider : public Component {
    REGISTER_BODY(Collider, Component)

public:
    Collider() = default;

    explicit Collider(Actor* owner, Rigidbody* rigidbody, bool isSensor, uint16 collisionLayer = CollisionLayer::Default) : Component(owner), m_Rigidbody(rigidbody), isTrigger(isSensor), collisionLayer(collisionLayer) { }

    ~Collider() override = default;

    void Start() override;

    PROPERTY() bool isTrigger = false;
    PROPERTY() Vector2 offset = { 0.0f, 0.0f };
    PROPERTY() float density = 1.;

    PROPERTY() uint16 collisionLayer = CollisionLayer::Default;

    void OnCollisionEnter(Collider* other) override;
    void OnCollisionExit(Collider* other)  override;
    void OnTriggerEnter(Collider* other)   override;
    void OnTriggerExit(Collider* other)    override;

    void SetCollisionLayer(uint16 layer);
    void SetFilter(uint16 category, uint16 mask);

    void ApplyFilter(uint16 category, uint16 mask);

protected:
    Rigidbody* m_Rigidbody{};
    b2FixtureDef fixtureDef;
};


#endif //SDLPROJECT_COLLIDER_H
