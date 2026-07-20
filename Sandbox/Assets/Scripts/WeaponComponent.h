//
// Created by rossi on 11/07/2026.
//

#ifndef SDLPROJECT_WEAPONCOMPONENT_H
#define SDLPROJECT_WEAPONCOMPONENT_H

#include <iostream>
#include "Engine/Game/Core/Component/Component.h"
#include "Engine/Game/Core/Math/Vector2.h"
#include "Weapon.h"

class WeaponComponent : public Component{
    REGISTER_BODY(WeaponComponent, Component)

public:
    void AddWeapon(Weapon* weapon){
        if(CanAddWeapon())
        {
            m_Weapons.push_back(weapon);
        }
        else {
            std::cerr << "Inventory full! Cannot add weapon." << std::endl;
        }
    }

    bool CanAddWeapon() const
    {
        return m_Weapons.size() < m_MaxWeapons;
    }

    Weapon* GetCurrentWeapon() const {
        if(m_Weapons.empty() || m_CurrentWeaponIndex >= m_Weapons.size()) {
            std::cerr << "No currently equipped weapons" << std::endl;
            return nullptr;
        }
        return m_Weapons[m_CurrentWeaponIndex];
    }

    void ChangeWeapon(Weapon* weapon, size_t indexAt) {
        if (indexAt < m_Weapons.size()) {
            if (m_Weapons[indexAt]) {
                delete m_Weapons[indexAt];
            }
            m_Weapons[indexAt] = weapon;
        }
        else {
            std::cerr << "Cannot change weapon: Index does not exist." << std::endl;
        }
    }

    Weapon* EquipWeapon(size_t indexAt) {
        if (m_Weapons.empty()) {
            std::cerr << "Cannot equip: Inventory is empty." << std::endl;
            return nullptr;
        }

        indexAt = indexAt % m_Weapons.size();

        m_CurrentWeaponIndex = (int) indexAt;

        return m_Weapons[m_CurrentWeaponIndex];
    }

    void Update(float deltaTime) override;
    bool TryShoot(Entity* entity, Vector2 targetWorldPos);

private:
    std::vector<Weapon*> m_Weapons;
    int m_CurrentWeaponIndex = 0;

    int m_MaxWeapons = 2;

    float m_ShootTime = 0.f;
};

#endif //SDLPROJECT_WEAPONCOMPONENT_H
