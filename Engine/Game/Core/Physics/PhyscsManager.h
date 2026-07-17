//
// Created by rossi on 17/07/2026.
//

#ifndef SDLPROJECT_PHYSCSMANAGER_H
#define SDLPROJECT_PHYSCSMANAGER_H

#include "box2d/b2_world.h"

class PhysicsManager{
public:
    static b2World* GetWorld() { return world; }

    static void Init(){
        world = new b2World(b2Vec2(0.f, 0.f));
    }

    static void Update(float deltaTime){
        world->Step(deltaTime, 6, 2);
    }

private:
    static b2World* world;
};

#endif //SDLPROJECT_PHYSCSMANAGER_H
