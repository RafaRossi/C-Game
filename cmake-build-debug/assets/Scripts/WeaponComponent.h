//
// Created by rossi on 11/07/2026.
//

#ifndef SDLPROJECT_WEAPONCOMPONENT_H
#define SDLPROJECT_WEAPONCOMPONENT_H

#include "Engine/Game/Core/Component/Component.h"
#include "Engine/Game/Core/Math/Vector2.h"

class WeaponComponent : public Component{
    REGISTER_BODY(WeaponComponent, Component)

public:
    PROPERTY() float fireRate = 0.2f;
    PROPERTY() float bulletSpeed = 800.0f;

    void Update(float deltaTime) override;
    bool TryShoot(Vector2 targetWorldPos);

protected:
    float m_ShootTime = 0.0f;
};

#endif //SDLPROJECT_WEAPONCOMPONENT_H
