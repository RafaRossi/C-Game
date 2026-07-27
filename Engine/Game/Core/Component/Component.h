//
// Created by rossi on 30/06/2026.
//

#ifndef SDLPROJECT_COMPONENT_H
#define SDLPROJECT_COMPONENT_H

#include <SDL3/SDL_render.h>
#include <string>
#include "../../../Game/Core/Macros/EngineMacros.h"

class Collider;

class Actor;

class Component {
INSTANCED(Component)
public:

    Component() = default;
    explicit Component(Actor* owner) : owner(owner) {}

    Actor* owner = nullptr;

    virtual void Start() { }
    virtual void Update(float deltaTime) { }
    virtual void LateUpdate(float deltaTime) { }

    virtual void* GetInstance() { return this; }

    virtual bool IsUnique() const { return false; }
    virtual bool CanBeRemoved() { return true; }

    virtual void OnCollisionEnter(Collider* other) {};
    virtual void OnCollisionExit(Collider* other)  {};
    virtual void OnTriggerEnter(Collider* other)   {}
    virtual void OnTriggerExit(Collider* other)    {}

    bool hasStarted = false;
};

#endif //SDLPROJECT_COMPONENT_H