//
// Created by rossi on 09/07/2026.
//

#ifndef SDLPROJECT_SHAPE_H
#define SDLPROJECT_SHAPE_H

#include <SDL3/SDL_render.h>
#include <string>

class Shape {
public:
    virtual ~Shape() = default;

    virtual void Draw(SDL_Renderer* renderer, const SDL_FRect& bounds, const SDL_Color& color) = 0;

    virtual std::string GetShapeName() const = 0;
    virtual Shape* Clone() const = 0;
};

#endif //SDLPROJECT_SHAPE_H
