//
// Created by rossi on 12/07/2026.
//

#ifndef SDLPROJECT_BULLETSTRATEGY_H
#define SDLPROJECT_BULLETSTRATEGY_H

#include <vector>
#include "Engine/Game/Core/Math/Vector2.h"
#include "Engine/Game/Core/Transform/Transform.h"
#include "DamageStrategy.h"

struct BulletStrategyContext
{
    Transform* target;
    Vector2* targetPosition;
};

class BulletStrategy
{
    BulletStrategy(BulletStrategyContext ctx);
public:
    virtual void OnBulletHit() = 0;


private:
    DamageStrategy* m_Damage;
};

#endif //SDLPROJECT_BULLETSTRATEGY_H
