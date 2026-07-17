//
// Created by rossi on 12/07/2026.
//

#ifndef SDLPROJECT_SMOOTHFOLLOW_H
#define SDLPROJECT_SMOOTHFOLLOW_H

#include "FollowStrategy.h"

class SmoothFollow : public FollowStrategy {
public:
    float smoothSpeed = 5.0f;

    Vector2 Calculate(const FollowContext& ctx) override {
        float t = 1.0f - std::exp(-smoothSpeed * ctx.deltaTime);
        return Vector2::Lerp(ctx.position, ctx.targetPos, t);
    }
};

#endif //SDLPROJECT_SMOOTHFOLLOW_H
