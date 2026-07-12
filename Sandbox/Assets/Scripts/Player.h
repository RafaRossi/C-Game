//
// Created by rossi on 11/07/2026.
//

#ifndef SDLPROJECT_PLAYER_H
#define SDLPROJECT_PLAYER_H

#include "Engine/Game/Core/Actor/Actor.h"
#include "Weapon.h"
#include "Engine/Game/Core/Inputs/InputManager.h"

class Player : public Component {
    REGISTER_BODY(Player, Component)
public:
    Player() { }
    ~Player() { }

    float moveSpeed = 500.f;

    Weapon* currentWeapon;

    void SetCurrentWeapon(Weapon* newWeapon){
        currentWeapon->OnUnnequip();
        currentWeapon = newWeapon;
        currentWeapon->OnEquip();
    }

    bool IsUnique()  { return true; }

    void Update(float deltaTime) override
    {
        auto moveInput = InputManager::Instance().GetAxis2D(SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_W, SDL_SCANCODE_S).Normalized();

        auto* transform = owner->transform();

        transform->position.x += moveInput.x * moveSpeed * deltaTime;
        transform->position.y += moveInput.y * moveSpeed * deltaTime;

        printf("\n (%f %f)", transform->position.x, transform->position.y);
    }

};



#endif //SDLPROJECT_PLAYER_H
