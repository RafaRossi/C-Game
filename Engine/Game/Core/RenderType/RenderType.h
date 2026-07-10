//
// Created by rossi on 09/07/2026.
//

#ifndef SDLPROJECT_RENDERTYPE_H
#define SDLPROJECT_RENDERTYPE_H

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include "../Component/Component.h"
#include "../Actor/Actor.h"

class RenderType {
public:
    virtual ~RenderType() = default;

    virtual void Draw(SDL_Renderer* renderer, const SDL_FRect& bounds, const Color& color) = 0;

    virtual std::string GetTypeName() const = 0;
    virtual RenderType* Clone() const = 0;
    virtual void AutoExposeField(FieldCollector& collector) {}
};

class ShapeRenderer : public RenderType {
    REGISTER_BODY(ShapeRenderer, RenderType)

public:
    PROPERTY() std::string teste;

    void Draw(SDL_Renderer* renderer, const SDL_FRect& bounds, const Color& color) override {

    }
};

#endif //SDLPROJECT_RENDERTYPE_H
