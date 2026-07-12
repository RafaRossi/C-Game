//
// Created by rossi on 10/07/2026.
//

#ifndef SDLPROJECT_SHAPERENDER_H
#define SDLPROJECT_SHAPERENDER_H


#include "RenderType.h"
#include "Engine/Game/Core/Shape/Shape.h"

class ShapeRender : public RenderType {
    REGISTER_BODY(ShapeRender, RenderType)
public:
    ~ShapeRender() = default;

    void Draw(SDL_Renderer* renderer, const SDL_FRect& bounds, const Color& color) override {
        m_Shape->Draw(renderer, bounds, color);
    }

    void SetShape(Shape* shape){
        m_Shape = shape;
    }

private:
    Shape* m_Shape = nullptr;
};
#endif //SDLPROJECT_SHAPERENDER_H
