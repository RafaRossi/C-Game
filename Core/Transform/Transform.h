//
// Created by rossi on 02/07/2026.
//

#ifndef SDLPROJECT_TRANSFORM_H
#define SDLPROJECT_TRANSFORM_H

#pragma once

#include "../Math/Vector2.h"

struct Transform {
    Vector2 position;
    float rotation = 0.0f;
    Vector2 size = { 100.f, 100.f};
};
#endif //SDLPROJECT_TRANSFORM_H
