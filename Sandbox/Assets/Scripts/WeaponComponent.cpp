//
// Created by rossi on 13/07/2026.
//
#include "WeaponComponent.h"
#include "Engine/Game/Core/Math/Vector2.h"

void WeaponComponent::Update(float deltaTime) {
    if(m_ShootTime > 0.0f)
    {
        m_ShootTime -= deltaTime;
    }
}

bool WeaponComponent::TryShoot(Entity* entity, Vector2 targetWorldPos) {

    if(m_ShootTime > 0.0f){
        return false;
    }

    m_ShootTime = GetCurrentWeapon()->GetShootFrequency() * (1 / entity->GetStat(Stats::AttackSpeed));
    GetCurrentWeapon()->Shoot(targetWorldPos);

    return true;
}

