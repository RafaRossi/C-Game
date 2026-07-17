//
// Created by rossi on 12/07/2026.
//

#ifndef SDLPROJECT_INSTANTFOLLOW_H
#define SDLPROJECT_INSTANTFOLLOW_H

#include "FollowStrategy.h"
#include "Engine/Game/Core/Math/Vector2.h"

class InstantFollow : public FollowStrategy {
public:
    Vector2 Calculate(const FollowContext& ctx) override {
        return ctx.targetPos;
    }
};

#endif //SDLPROJECT_INSTANTFOLLOW_H
