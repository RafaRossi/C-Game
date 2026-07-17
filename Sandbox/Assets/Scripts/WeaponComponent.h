//
// Created by rossi on 11/07/2026.
//

#ifndef SDLPROJECT_WEAPONCOMPONENT_H
#define SDLPROJECT_WEAPONCOMPONENT_H

#include "Engine/Game/Core/Component/Component.h"
#include "Engine/Game/Core/Math/Vector2.h"
#include "Weapon.h"

class WeaponComponent : public Component{
    REGISTER_BODY(WeaponComponent, Component)

public:
    void SetWeapon(Weapon* weapon){
        m_Weapon = weapon;
    }

    Weapon* GetCurrentWeapon() const { return m_Weapon; }

    void Update(float deltaTime) override;
    bool TryShoot(Entity* entity, Vector2 targetWorldPos);

private:
    Weapon* m_Weapon;

    float m_ShootTime = 0.f;
};

#endif //SDLPROJECT_WEAPONCOMPONENT_H
