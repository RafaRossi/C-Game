//
// Created by rossi on 13/07/2026.
//
#include "WeaponComponent.h"
#include "Engine/Game/Core/Math/Vector2.h"
#include "Engine/Game/Game.h"
#include "Engine/Game/Core/Inputs/InputManager.h"
#include "Sandbox/Assets/Premades/Premades.h"

void WeaponComponent::Update(float deltaTime) {
    if(m_ShootTime > 0.0f)
    {
        m_ShootTime -= deltaTime;
    }

    if(InputManager::Instance().IsMouseButtonDown(1)){

        Vector2 screenMousePos = InputManager::Instance().GetMousePosition();
        Vector2 targetWorldPos = Game::Instance().GetScene()->GetCamera()->ScreenToWorld(screenMousePos);

        TryShoot(targetWorldPos);
    }
}

bool WeaponComponent::TryShoot(Vector2 targetWorldPos) {

    if(m_ShootTime > 0.0f){
        return false;
    }

    m_ShootTime = fireRate;

    Vector2 sourcePosition = owner->GetWorldPosition();

    Vector2 direction = (targetWorldPos - sourcePosition).Normalized();

    Premades::Bullet(direction, bulletSpeed, sourcePosition, 0.f);

    return true;
}

