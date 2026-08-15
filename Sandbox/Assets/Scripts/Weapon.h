//
// Created by rossi on 11/07/2026.
//

#ifndef SDLPROJECT_WEAPON_H
#define SDLPROJECT_WEAPON_H

#include "Entity.h"
#include "Engine/Game/Core/Actor/Actor.h"
#include "box2d/b2_types.h"
#include "Engine/Game/Core/Collision/CollisionMask.h"

class Weapon{

public:
    explicit Weapon(Entity* entity, uint16 weaponCollisionLayer = CollisionLayer::Default){
        m_Entity = entity;
        m_WeaponCollisionLayer = weaponCollisionLayer;
    }

    virtual ~Weapon() = default;

    virtual void Shoot(Vector2 targetWorldPos) = 0;

    virtual void OnEquip();
    virtual void OnUnnequip();

    virtual float GetShootFrequency() {
        return m_ShootFrequency * m_Entity->GetStat(Stats::AttackSpeed);
    }

protected:
    Entity* m_Entity;
    float m_ShootFrequency{};

    uint16 m_WeaponCollisionLayer = CollisionLayer::Default;
};

class ProjectileGun : public Weapon
{
public:
    PROPERTY() float bulletSpeed = 800.f;

    explicit ProjectileGun(Entity* entity, uint16 weaponCollisionLayer = CollisionLayer::Default, float shootFrequency = 0.5f) : Weapon(entity, weaponCollisionLayer)
    {
        m_ShootFrequency = shootFrequency;
    }

    void Shoot(Vector2 targetWorldPos) override;
};


#endif //SDLPROJECT_WEAPON_H
