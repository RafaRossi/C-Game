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
    ShapeRender();

    explicit ShapeRender(Shape* shape) {
        m_Shape = shape;
    }

    ~ShapeRender() override = default;

    void Draw(SDL_Renderer* renderer, const SDL_FRect& bounds, const Color32& color) override;

    void SetShape(Shape* shape);

private:
    Shape* m_Shape = nullptr;
};
#endif //SDLPROJECT_SHAPERENDER_H
