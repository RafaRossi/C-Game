//
// Created by rossi on 01/08/2026.
//

#ifndef SDLPROJECT_COLLISIONMASK_H
#define SDLPROJECT_COLLISIONMASK_H

#include "box2d/b2_types.h"

namespace CollisionLayer{
    constexpr uint16 Default          = 1 << 0;
    constexpr uint16 Player           = 1 << 1;
    constexpr uint16 Enemy            = 2 << 1;
    constexpr uint16 Environment      = 3 << 1;
    constexpr uint16 UI               = 3 << 1;

    constexpr uint16 All              = 0xFFFF;
    constexpr uint16 None             = 0x0000;
}

#endif //SDLPROJECT_COLLISIONMASK_H
