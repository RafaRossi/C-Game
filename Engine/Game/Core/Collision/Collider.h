//
// Created by rossi on 17/07/2026.
//
#pragma once
#ifndef SDLPROJECT_COLLIDER_H
#define SDLPROJECT_COLLIDER_H


#include "Engine/Game/Core/Component/Component.h"
#include "Engine/Game/Core/Math/Vector2.h"

class Collider : public Component {
    REGISTER_BODY(Collider, Component)

public:
    ~Collider() override = default;

    void Start() override { }

    PROPERTY() bool isTrigger = false;
    PROPERTY() Vector2 offset = { 0.0f, 0.0f };
};


#endif //SDLPROJECT_COLLIDER_H
