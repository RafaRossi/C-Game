//
// Created by rossi on 11/07/2026.
//

#ifndef SDLPROJECT_PLAYER_H
#define SDLPROJECT_PLAYER_H

#include "Engine/Game/Core/Actor/Actor.h"
#include "Weapon.h"
#include "Engine/Game/Core/Inputs/InputManager.h"
#include "WeaponComponent.h"
#include "Entity.h"

class Player : public Entity {
REGISTER_BODY(Player, Entity)

public:
    Player(){
        SetBaseStat(Stats::Speed, 500.f);
        SetBaseStat(Stats::AttackSpeed, .5f);
    }

    ~Player() override = default;

    bool IsUnique()  { return true; }

    void Update(float deltaTime) override;

    void SetWeaponComponent(WeaponComponent* weaponComponent) { m_Weapon = weaponComponent; }

private:
    WeaponComponent* m_Weapon = nullptr;
};



#endif //SDLPROJECT_PLAYER_H
