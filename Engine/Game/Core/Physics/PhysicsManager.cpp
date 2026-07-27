#include "box2d/b2_world.h"

#include "PhysicsManager.h"

//
// Created by rossi on 17/07/2026.
//
b2World* PhysicsManager::world = nullptr;
GameContactListener PhysicsManager::m_ContactListener;