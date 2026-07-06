//
// Created by rossi on 30/06/2026.
//

#ifndef SDLPROJECT_COMPONENT_H
#define SDLPROJECT_COMPONENT_H

#include <SDL3/SDL_render.h>
#include <string>

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
};

#define COMPONENT_BODY(Type) \
public: \
    virtual Component* Clone() const override { \
        return new Type(*this); \
    } \
    virtual std::string GetClassName() const override { \
        return #Type; \
    } \
private:

#endif //SDLPROJECT_COMPONENT_H