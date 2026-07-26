//
// Created by rossi on 25/07/2026.
//
#include "ShapeRender.h"
#include "Engine/Game/Core/Shape/Shape.h"

void ShapeRender::Draw(SDL_Renderer *renderer, const SDL_FRect &bounds, const Color32 &color) {
    m_Shape->Draw(renderer, bounds, color);
}

void ShapeRender::SetShape(Shape *shape) {
    m_Shape = shape;
}

ShapeRender::ShapeRender() = default;

