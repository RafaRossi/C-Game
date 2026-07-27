//
// Created by rossi on 17/07/2026.
//
#pragma once
#ifndef SDLPROJECT_COLLIDER_H
#define SDLPROJECT_COLLIDER_H


#include "Engine/Game/Core/Component/Component.h"
#include "Engine/Game/Core/Math/Vector2.h"
#include "Engine/Game/Core/Rigidbody/Rigidbody.h"

class Collider : public Component {
    REGISTER_BODY(Collider, Component)

public:
    Collider() = default;

    explicit Collider(Actor* owner, Rigidbody* rigidbody, bool isSensor) : Component(owner), m_Rigidbody(rigidbody), isTrigger(isSensor) { }

    ~Collider() override = default;

    void Start() override;

    PROPERTY() bool isTrigger = false;
    PROPERTY() Vector2 offset = { 0.0f, 0.0f };

    void OnCollisionEnter(Collider* other) override;
    void OnCollisionExit(Collider* other)  override;
    void OnTriggerEnter(Collider* other)   override;
    void OnTriggerExit(Collider* other)    override;

protected:
    Rigidbody* m_Rigidbody{};
};


#endif //SDLPROJECT_COLLIDER_H
