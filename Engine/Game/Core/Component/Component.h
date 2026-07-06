//
// Created by rossi on 30/06/2026.
//

#ifndef SDLPROJECT_COMPONENT_H
#define SDLPROJECT_COMPONENT_H

#include <SDL3/SDL_render.h>
#include <string>
#include "../../../Editor/Macros/EngineMacros.h"

#ifdef TR_EDITOR
#include "../../../Editor/PropertyType/PropertyType.h"
#endif

class Actor;

class Component {
public:
    Actor* owner = nullptr;

    virtual ~Component() = default;
    virtual void Update(float deltaTime) {}
    virtual void Draw(SDL_Renderer* renderer) {}

    virtual void* GetInstance() { return this; }

    virtual std::string GetClassName() const = 0;
    virtual Component* Clone() const = 0;

    virtual bool IsUnique() const { return false; }
    virtual bool CanBeRemoved() { return true; }

#ifdef TR_EDITOR
    virtual void AutoExposeField(FieldCollector& collector) { }
#endif
};

#endif //SDLPROJECT_COMPONENT_H