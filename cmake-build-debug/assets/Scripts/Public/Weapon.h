//
// Created by rossi on 11/07/2026.
//

#ifndef SDLPROJECT_WEAPON_H
#define SDLPROJECT_WEAPON_H

class Weapon{

public:
    Weapon(){}
    ~Weapon() {}

    float shootFrequency;
    virtual void Shoot();

    virtual void OnEquip();
    virtual void OnUnnequip();
};

class StandardGun : Weapon
{
    StandardGun() : Weapon { }
    {
        shootFrequency = 0.5f;
    }


};

#endif //SDLPROJECT_WEAPON_H
