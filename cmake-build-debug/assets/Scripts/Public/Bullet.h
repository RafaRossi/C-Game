//
// Created by rossi on 11/07/2026.
//

#ifndef SDLPROJECT_BULLET_H
#define SDLPROJECT_BULLET_H

#include "Engine/Game/Core/Actor/Actor.h"
#include "Engine/Game/Core/Renderer/Renderer.h"

class Bullet : Component {

public:
    Bullet(){
        AddComponent<Renderer>();
    }

    void Shoot(Vector2 direction)
    {

    }

    float bulletDamage = 1.f;
};

#endif //SDLPROJECT_BULLET_H
