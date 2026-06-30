//
// Created by rossi on 29/06/2026.
//

#ifndef SDLPROJECT_RENDERER_H
#define SDLPROJECT_RENDERER_H


#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>

struct Renderer {
    SDL_Color color = {255, 255, 255, 255};
    SDL_Texture* sprite = nullptr;

    int orderInLayer = 0;
};


#endif //SDLPROJECT_RENDERER_H
