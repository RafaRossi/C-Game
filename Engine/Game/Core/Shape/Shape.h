//
// Created by rossi on 09/07/2026.
//

#ifndef SDLPROJECT_SHAPE_H
#define SDLPROJECT_SHAPE_H

#include <SDL3/SDL_render.h>
#include <string>
#include "Engine/Game/Core/Color/Color.h"

class Shape {
public:
    virtual void Draw(SDL_Renderer* renderer, const SDL_FRect& bounds, const Color& color) = 0;
};

class Square : public Shape{
public:
    void Draw(SDL_Renderer* renderer, const SDL_FRect& bounds, const Color& color) override {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &bounds);
    }
};

#endif //SDLPROJECT_SHAPE_H
