//
// Created by rossi on 11/07/2026.
//

#ifndef SDLPROJECT_WEAPON_H
#define SDLPROJECT_WEAPON_H

#include "Entity.h"
#include "Engine/Game/Core/Actor/Actor.h"

class Weapon{

public:
    explicit Weapon(Entity* entity){
        m_Entity = entity;
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
};

class StandardGun : public Weapon
{
public:
    PROPERTY() float bulletSpeed = 800.f;

    explicit StandardGun(Entity* entity) : Weapon(entity)
    {
        m_ShootFrequency = 0.5f;
    }

    void Shoot(Vector2 targetWorldPos) override;
};

#endif //SDLPROJECT_WEAPON_H
