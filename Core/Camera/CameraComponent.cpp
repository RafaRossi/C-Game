
#include "CameraComponent.h"


void CameraComponent::Apply(SDL_Renderer *renderer) {
    int w, h;
    SDL_GetCurrentRenderOutputSize(renderer, &w, &h);

    RenderBackground(renderer);

    SDL_SetRenderScale(renderer, zoom, zoom);

    SDL_FPoint offset = -owner->GetWorldPosition() * zoom;
    SDL_Rect viewport = {(int)offset.x, (int)offset.y, (int)(w/zoom), (int)(h/zoom)};

    SDL_SetRenderViewport(renderer, &viewport);
}

void CameraComponent::RenderBackground(SDL_Renderer *renderer) {
    SDL_Color bg = {20, 30, 45, 255};
    SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a);
    SDL_RenderClear(renderer);
}
