//
// Created by rossi on 11/07/2026.
//

#ifndef SDLPROJECT_PLAYER_H
#define SDLPROJECT_PLAYER_H

#include "Engine/Game/Core/Actor/Actor.h"
#include "Engine/Game/Game.h"
#include "WeaponComponent.h"
#include "Engine/Game/Core/Inputs/InputManager.h"
#include "Engine/Game/Core/Movement/ProjectileMovementComponent.h"
#include "Sandbox/Assets/Scripts/WeaponComponent.h"
#include "Entity.h"

class Player : public Entity {
    REGISTER_BODY(Player, Entity)

public:
    Player(){
        SetBaseStat(Stats::Speed, 500.f);
        currentWeapon = nullptr;
    }

    ~Player() override = default;

    WeaponComponent* currentWeapon;

    void SetCurrentWeapon(WeaponComponent* newWeapon){
        currentWeapon = newWeapon;
    }

    bool IsUnique()  { return true; }

    void Update(float deltaTime) override
    {
        auto moveInput = InputManager::Instance().GetAxis2D(SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_W, SDL_SCANCODE_S).Normalized();

        auto* transform = owner->transform();

        transform->position = transform->position + (moveInput * GetStat(Stats::Speed) * deltaTime);
    }
};

#endif //SDLPROJECT_PLAYER_H
