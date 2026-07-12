//
// Created by rossi on 02/07/2026.
//

#ifndef SDLPROJECT_TRANSFORM_H
#define SDLPROJECT_TRANSFORM_H

#pragma once

#include <string>
#include "../Math/Vector2.h"
#include "../Component/Component.h"

class Transform : public Component {
REGISTER_BODY(Transform, Component)


public:
    PROPERTY() Vector2 position;
    PROPERTY() float rotation = 0.0f;
    PROPERTY() Vector2 scale = { 1.f, 1.f};

    void* GetInstance() override { return this; }

    bool IsUnique() const override { return true; }
    bool CanBeRemoved() override { return false; }
};
#endif //SDLPROJECT_TRANSFORM_H
