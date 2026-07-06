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
COMPONENT_BODY(Transform)

public:
    Vector2 position;
    float rotation = 0.0f;
    Vector2 size = { 100.f, 100.f};

    void* GetInstance() { return this; }
};
#endif //SDLPROJECT_TRANSFORM_H
