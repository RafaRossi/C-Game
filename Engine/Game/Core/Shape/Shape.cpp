//
// Created by rossi on 25/07/2026.
//
#include <SDL3/SDL_render.h>
#include "Shape.h"
#include "Engine/Game/Core/Renderer/Renderer.h"

void Square::Draw(SDL_Renderer *renderer, const SDL_FRect &bounds, const Color32 &color) {
    Renderer::SetRenderDrawColor(renderer, color);
    SDL_RenderFillRect(renderer, &bounds);
}

