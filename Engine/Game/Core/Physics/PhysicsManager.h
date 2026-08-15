//
// Created by rossi on 17/07/2026.
//

#ifndef SDLPROJECT_PHYSICSMANAGER_H
#define SDLPROJECT_PHYSICSMANAGER_H

#include <iostream>
#include <unordered_map>

#include "box2d/b2_world.h"
#include "GameContactListener.h"
#include "Engine/Game/Core/Collision/CollisionMask.h"

class PhysicsManager{
public:
    static b2World* GetWorld() { return world; }

    static void Init(){
        world = new b2World(b2Vec2(0.f, 0.f));
        world->SetContactListener(&m_ContactListener);

        PhysicsManager::SetLayerCollision(CollisionLayer::Player, CollisionLayer::Player, false);
        PhysicsManager::SetLayerCollision(CollisionLayer::Player, CollisionLayer::Enemy,  true);
        PhysicsManager::SetLayerCollision(CollisionLayer::Enemy,  CollisionLayer::Enemy,  false);
        PhysicsManager::SetLayerCollision(CollisionLayer::Default,  CollisionLayer::All, true);
        PhysicsManager::SetLayerCollision(CollisionLayer::UI,  CollisionLayer::All, false);

        PhysicsManager::SetLayerCollision(CollisionLayer::Default, CollisionLayer::Player, true);
        PhysicsManager::SetLayerCollision(CollisionLayer::Default, CollisionLayer::Enemy,  true);
        PhysicsManager::SetLayerCollision(CollisionLayer::Default, CollisionLayer::Default,  true);
    }

    static void Update(float deltaTime){
        world->Step(deltaTime, 6, 2);
    }

    static void SetLayerCollision(uint16 layerA, uint16 layerB, bool collides){
        if (layerB == CollisionLayer::All) {
            for (auto& [layer, mask] : m_LayerMatrix) {
                SetLayerCollision(layerA, layer, collides);
            }
            return;
        }

        if(collides){
            m_LayerMatrix[layerA] |= layerB;
            m_LayerMatrix[layerB] |= layerA;
        }else{
            m_LayerMatrix[layerA] &= ~layerB;
            m_LayerMatrix[layerB] &= ~layerA;
        }
    }

    static uint16 GetMaskForLayer(uint16 layer){
        return m_LayerMatrix[layer];
    }

private:
    static b2World* world;
    static GameContactListener m_ContactListener;
    static std::unordered_map<uint16, uint16> m_LayerMatrix;
};

#endif //SDLPROJECT_PHYSICSMANAGER_H
