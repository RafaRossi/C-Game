//
// Created by rossi on 11/07/2026.
//

#ifndef SDLPROJECT_PLAYER_H
#define SDLPROJECT_PLAYER_H

#include "Engine/Game/Core/Actor/Actor.h"
#include "Weapon.h"

class Player : public Component {
    REGISTER_BODY(Player, Component)
public:
    Player() { }
    ~Player() { }

    float moveSpeed;

    Weapon* currentWeapon;

    void SetCurrentWeapon(Weapon* newWeapon){
        currentWeapon->OnUnnequip();
        currentWeapon = newWeapon;
        currentWeapon->OnEquip();
    }

    bool IsUnique()  { return true; }

};



#endif //SDLPROJECT_PLAYER_H
