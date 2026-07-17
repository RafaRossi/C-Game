//
// Created by rossi on 17/07/2026.
//
#include "Player.h"
#include "Engine/Game/Game.h"

void Player::Update(float deltaTime) {
    auto moveInput = InputManager::Instance().GetAxis2D(SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_W, SDL_SCANCODE_S).Normalized();

    auto* transform = owner->transform();

    transform->position = transform->position + (moveInput * GetStat(Stats::Speed) * deltaTime);

    if(InputManager::Instance().IsMouseButtonDown(1) && m_Weapon){

        Vector2 screenMousePos = InputManager::Instance().GetMousePosition();
        Vector2 targetWorldPos = Game::Instance().GetScene()->GetCamera()->ScreenToWorld(screenMousePos);

        m_Weapon->TryShoot(this, targetWorldPos);
    }
}

