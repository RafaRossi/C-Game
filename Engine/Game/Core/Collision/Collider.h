//
// Created by rossi on 17/07/2026.
//
#pragma once
#ifndef SDLPROJECT_COLLIDER_H
#define SDLPROJECT_COLLIDER_H


#include "Engine/Game/Core/Component/Component.h"
#include "Engine/Game/Core/Math/Vector2.h"
#include "Engine/Game/Core/Actor/Actor.h"
#include "Engine/Game/Core/Rigidbody/Rigidbody.h"

class Collider : public Component {
    REGISTER_BODY(Collider, Component)

public:
    PROPERTY() bool isTrigger = false;
    PROPERTY() Vector2 offset = { 0.0f, 0.0f };
};

class BoxCollider : public Collider{
    REGISTER_BODY(BoxCollider, Collider)

public:
    BoxCollider();

    PROPERTY() Vector2 size = { 100.f, 100.f };

private:
    Rigidbody* m_Rigidbody;
    b2PolygonShape boxShape;
};


#endif //SDLPROJECT_COLLIDER_H
