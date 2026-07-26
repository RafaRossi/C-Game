//
// Created by rossi on 09/07/2026.
//

#ifndef SDLPROJECT_RENDERTYPE_H
#define SDLPROJECT_RENDERTYPE_H

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include "../Component/Component.h"
#include "../Actor/Actor.h"
#include "Engine/Game/Core/Color/Color.h"

class RenderType {
INSTANCED(RenderType)
public:
    virtual void Draw(SDL_Renderer* renderer, const SDL_FRect& bounds, const Color32& color) = 0;

    void Draw(SDL_Renderer* renderer, const SDL_FRect& bounds, const Color& color)
    {
        Draw(renderer, bounds, Color32(color.r, color.g, color.b, color.a));
    }
};

#endif //SDLPROJECT_RENDERTYPE_H
