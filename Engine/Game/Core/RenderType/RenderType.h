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
INSTANCED(RenderType)

public:
    virtual void Draw(SDL_Renderer* renderer, const SDL_FRect& bounds, const Color& color) = 0;
};

#endif //SDLPROJECT_RENDERTYPE_H
