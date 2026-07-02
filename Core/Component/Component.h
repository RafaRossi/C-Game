//
// Created by rossi on 30/06/2026.
//

#ifndef SDLPROJECT_COMPONENT_H
#define SDLPROJECT_COMPONENT_H


#include <SDL3/SDL_render.h>

class Actor;

class Component {
public:
    Actor* owner = nullptr;

    virtual ~Component() = default;
    virtual void Update(float deltaTime) {}
    virtual void Draw(SDL_Renderer* renderer) {}
};


#endif //SDLPROJECT_COMPONENT_H
