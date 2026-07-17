
#include "CameraComponent.h"
#include "../../Game.h"


void CameraComponent::Apply(SDL_Renderer *renderer) {
    int w, h;
    SDL_GetCurrentRenderOutputSize(renderer, &w, &h);

    SDL_Rect fullViewport = {0, 0, w, h};
    SDL_SetRenderViewport(renderer, &fullViewport);

    RenderBackground(renderer);
    SDL_SetRenderScale(renderer, zoom, zoom);
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
    if(!followTarget || target == nullptr || m_FollowStrategy == nullptr) return;

    Vector2 targetPos   = target->owner->GetWorldPosition();
    Vector2 camPos      = owner->transform()->position;

    Vector2 desiredPos = targetPos;

    if (deadZone.width > 0.0f || deadZone.height > 0.0f) {
        float halfW = deadZone.width  / 2.0f;
        float halfH = deadZone.height / 2.0f;
        Vector2 delta = targetPos - camPos;

        desiredPos = camPos;

        if (delta.x >  halfW) desiredPos.x = desiredPos.x - halfW;
        if (delta.x < -halfW) desiredPos.x = desiredPos.x + halfW;
        if (delta.y >  halfH) desiredPos.y = desiredPos.y - halfH;
        if (delta.y < -halfH) desiredPos.y = desiredPos.y + halfH;
    }

    FollowContext ctx = { camPos, desiredPos, deltaTime };

    Vector2 newPos = m_FollowStrategy->Calculate(ctx);

    if (bounds.enabled) {
        newPos.x = Math::Clamp(newPos.x, bounds.min.x, bounds.max.x);
        newPos.y = Math::Clamp(newPos.y, bounds.min.y, bounds.max.y);
    }

    owner->transform()->position = newPos;
}

Vector2 CameraComponent::WorldToScreen(Vector2 worldPos) {
    int w, h;
    SDL_GetCurrentRenderOutputSize(Game::Instance().GetRenderer(), &w, &h);

    Vector2 camPos = owner->GetWorldPosition();

    float drawX = worldPos.x - camPos.x + (w / zoom) / 2.0f;
    float drawY = worldPos.y - camPos.y + (h / zoom) / 2.0f;

    return Vector2{drawX, drawY};
}

Vector2 CameraComponent::ScreenToWorld(Vector2 screenPos) {
    int w, h;
    SDL_GetCurrentRenderOutputSize(Game::Instance().GetRenderer(), &w, &h);

    Vector2 camPos = owner->GetWorldPosition();

    float worldX = screenPos.x + camPos.x - (w / zoom) / 2.0f;
    float worldY = screenPos.y + camPos.y - (h / zoom) / 2.0f;

    return Vector2{worldX, worldY};
}