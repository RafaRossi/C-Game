//
// Created by rossi on 10/07/2026.
//

#ifndef SDLPROJECT_SHAPERENDER_H
#define SDLPROJECT_SHAPERENDER_H


#include "RenderType.h"

class Shape;

class ShapeRender : public RenderType {
    REGISTER_BODY(ShapeRender, RenderType)

public:
    PROPERTY() Shape* shape;
    void Draw(SDL_Renderer* renderer, const SDL_FRect& bounds, const Color& color) override {

    }
};

class Shape {
INSTANCED(Shape)
};
#endif //SDLPROJECT_SHAPERENDER_H
