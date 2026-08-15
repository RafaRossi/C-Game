//
// Created by rossi on 17/07/2026.
//
#include "Weapon.h"
#include "Sandbox/Assets/Premades/Premades.h"

void ProjectileGun::Shoot(Vector2 targetWorldPos) {
    Vector2 sourcePosition = m_Entity->owner->GetWorldPosition();

    Vector2 direction = (targetWorldPos - sourcePosition).Normalized();

    Premades::Bullet(direction, bulletSpeed, sourcePosition, 0.f, m_WeaponCollisionLayer);
}

void Weapon::OnEquip() {

}

void Weapon::OnUnnequip() {

}