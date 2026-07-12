
#include "CameraComponent.h"


void CameraComponent::Apply(SDL_Renderer *renderer) {
    int w, h;

    SDL_GetCurrentRenderOutputSize(renderer, &w, &h);

    RenderBackground(renderer);

    SDL_SetRenderScale(renderer, zoom, zoom);

    Vector2 camPos = owner->GetWorldPosition();

    float vx = w / 2.0f - camPos.x * zoom;
    float vy = h / 2.0f - camPos.y * zoom;

    int vpW = w + (int)std::max(0.0f, -vx);
    int vpH = h + (int)std::max(0.0f, -vy);

    SDL_Rect viewport = {(int)vx, (int)vy, vpW, vpH};

    SDL_SetRenderViewport(renderer, &viewport);
}

void CameraComponent::RenderBackground(SDL_Renderer *renderer) {
    int w, h;
    SDL_GetCurrentRenderOutputSize(renderer, &w, &h);

    SDL_SetRenderDrawColor(renderer,
                           backgroundColor.r,
                           backgroundColor.g,
                           backgroundColor.b,
                           backgroundColor.a);

    SDL_FRect fullRect = {0.0f, 0.0f, (float)w, (float)h};
    SDL_RenderFillRect(renderer, &fullRect);
}

void CameraComponent::Update(float deltaTime) {
    if(!followTarget || target == nullptr) return;

    Vector2 targetPos   = target->owner->GetWorldPosition();
    Vector2 camPos      = owner->transform()->position;

    Vector2 desiredPos  = camPos;

    if(deadZone.width > 0.0f || deadZone.height > 0.0f){
        float halfW = deadZone.width  / 2.0f;
        float halfH = deadZone.height / 2.0f;

        Vector2 delta = targetPos - camPos;

        if(delta.x >  halfW) desiredPos.x = targetPos.x - halfW;
        if(delta.x < -halfW) desiredPos.x = targetPos.x + halfW;
        if(delta.y >  halfH) desiredPos.y = targetPos.y - halfH;
        if(delta.y < -halfH) desiredPos.y = targetPos.y + halfH;
    }else{
        desiredPos = targetPos;
    }

    float t = 1.0f - std::exp(-smoothSpeed * deltaTime);
    Vector2 newPos = Vector2::Lerp(camPos, desiredPos, t);

    if(bounds.enabled){
        newPos.x = Math::Clamp(newPos.x, bounds.min.x, bounds.max.x);
        newPos.y = Math::Clamp(newPos.y, bounds.min.y, bounds.max.y);
    }

    owner->transform()->position = newPos;
}
