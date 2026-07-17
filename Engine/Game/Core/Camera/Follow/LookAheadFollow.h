#ifndef SDLPROJECT_LOOKAHEADFOLLOW_H
#define SDLPROJECT_LOOKAHEADFOLLOW_H

#include "FollowStrategy.h"
#include "../../Math/Math.h"
#include <cmath>

class LookAheadFollow : public FollowStrategy {
public:
    float   mainSmoothSpeed      = 5.0f;
    float   lookAheadSmoothSpeed = 8.0f;
    Vector2 maxLookAhead         = {250.0f, 150.0f};

    Vector2 Calculate(const FollowContext& ctx) override {
        if (ctx.deltaTime <= 0.0f) return ctx.position;

        if (!m_IsInitialized) {
            m_LastTargetPos = ctx.targetPos;
            m_IsInitialized = true;
        }

        Vector2 deltaMove = ctx.targetPos - m_LastTargetPos;
        float speedX = deltaMove.x / ctx.deltaTime;
        float speedY = deltaMove.y / ctx.deltaTime;
        m_LastTargetPos = ctx.targetPos;

        if (std::abs(speedX) > 15.0f) {
            m_TargetOffset.x = (speedX > 0) ? maxLookAhead.x : -maxLookAhead.x;
        } else if (std::abs(speedX) < 2.0f) {
            m_TargetOffset.x = 0.0f;
        }

        if (std::abs(speedY) > 15.0f) {
            m_TargetOffset.y = (speedY > 0) ? maxLookAhead.y : -maxLookAhead.y;
        } else if (std::abs(speedY) < 2.0f) {
            m_TargetOffset.y = 0.0f;
        }

        float offsetT = 1.0f - std::exp(-lookAheadSmoothSpeed * ctx.deltaTime);
        m_CurrentOffset = Vector2::Lerp(m_CurrentOffset, m_TargetOffset, offsetT);

        Vector2 desiredPos = {
                ctx.targetPos.x + m_CurrentOffset.x,
                ctx.targetPos.y + m_CurrentOffset.y
        };

        return Vector2::SmoothDamp(ctx.position, desiredPos, mainSmoothSpeed, ctx.deltaTime);
    }

private:
    bool    m_IsInitialized = false;
    Vector2 m_LastTargetPos = {0.0f, 0.0f};
    Vector2 m_CurrentOffset = {0.0f, 0.0f};
    Vector2 m_TargetOffset  = {0.0f, 0.0f};
};

#endif