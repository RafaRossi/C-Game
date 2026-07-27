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

public:
    explicit Player(Actor* actor);

    ~Player() override = default;

    bool IsUnique()  { return true; }

    void Update(float deltaTime) override;

    void SetWeaponComponent(WeaponComponent* weaponComponent) { m_Weapon = weaponComponent; }
    WeaponComponent* GetWeaponComponent() { return m_Weapon; }

private:
    WeaponComponent* m_Weapon = nullptr;

    float m_ScrollCooldown = 0.f;
    const float SCROLL_DELAY = .2f;

    Vector2 m_PlayerSize = { 16, 16 };
};



#endif //SDLPROJECT_PLAYER_H
