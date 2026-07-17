//
// Created by rossi on 11/07/2026.
//

#ifndef SDLPROJECT_BULLET_H
#define SDLPROJECT_BULLET_H

#include "Engine/Game/Core/Actor/Actor.h"
#include "Engine/Game/Core/Renderer/Renderer.h"
#include "BulletStrategy.h"

class Bullet : public Component {
    REGISTER_BODY(Bullet, Component)

public:


    float bulletDamage = 1.f;
};

#endif //SDLPROJECT_BULLET_H
