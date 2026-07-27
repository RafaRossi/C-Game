//
// Created by rossi on 17/07/2026.
//

#ifndef SDLPROJECT_PHYSICSMANAGER_H
#define SDLPROJECT_PHYSICSMANAGER_H

#include "box2d/b2_world.h"
#include "GameContactListener.h"

class PhysicsManager{
public:
    static b2World* GetWorld() { return world; }

    static void Init(){
        world = new b2World(b2Vec2(0.f, 0.f));
        world->SetContactListener(&m_ContactListener);
    }

    static void Update(float deltaTime){
        world->Step(deltaTime, 6, 2);
    }

private:
    static b2World* world;
    static GameContactListener m_ContactListener;
};

#endif //SDLPROJECT_PHYSICSMANAGER_H
