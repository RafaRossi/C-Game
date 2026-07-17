//
// Created by rossi on 12/07/2026.
//

#ifndef SDLPROJECT_FOLLOWSTRATEGY_H
#define SDLPROJECT_FOLLOWSTRATEGY_H

#include <string>
#include "Engine/Game/Core/Math/Vector2.h"

struct FollowContext {
    Vector2 position;
    Vector2 targetPos;

    float deltaTime;
};

class FollowStrategy {
public:
    virtual ~FollowStrategy() = default;
    virtual Vector2 Calculate(const FollowContext& ctx) = 0;
};

#endif //SDLPROJECT_FOLLOWSTRATEGY_H
