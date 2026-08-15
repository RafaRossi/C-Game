//
// Created by rossi on 11/07/2026.
//

#ifndef SDLPROJECT_PREMADES_H
#define SDLPROJECT_PREMADES_H

#include <utility>

#include "Engine/Game/Core/Actor/Actor.h"
#include "box2d/b2_types.h"

class Premades{
public:
    static Actor* PlayerObject(Vector2 position, float rotation);

    static Actor* GenericActor(const std::string& actorName, Actor* parent, Vector2 position, float rotation);

    static Actor* Bullet(Vector2 direction, float speed, Vector2 position, float rotation, uint16 collisionMask);
};

#endif //SDLPROJECT_PREMADES_H
