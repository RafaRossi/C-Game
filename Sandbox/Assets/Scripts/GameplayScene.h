//
// Created by rossi on 11/07/2026.
//

#ifndef SDLPROJECT_GAMEPLAYSCENE_H
#define SDLPROJECT_GAMEPLAYSCENE_H


#include "Engine/Game/Core/Scene/Scene.h"
#include "Sandbox/Assets/Premades/Premades.h"
#include "Engine/Game/Core/Camera/Follow/InstantFollow.h"

class GameplayScene : public Scene {

public:

    ~GameplayScene() = default;

    void InitializeScene() override {
        auto* playerActor = Premades::PlayerObject({ 0.f, 0.f }, 0);
        auto* playerComponent = playerActor->GetComponent<Player>();

        auto* weaponActor = Premades::GenericActor("Weapon", playerActor, playerActor->GetWorldPosition(), 0.f);

        auto* weaponComponent = weaponActor->AddComponent<WeaponComponent>();
        playerComponent->SetWeaponComponent(weaponComponent);

        auto weapon = new StandardGun(playerComponent);
        weaponComponent->AddWeapon(weapon);

        auto* camera = (CreateActor("Main Camera"))->AddComponent<CameraComponent>();
        SetMainCamera(camera);

        camera->followTarget  = true;
        camera->target        = playerActor->transform();

        camera->deadZone = {0.0f, 0.0f};

        camera->bounds.enabled = false;
        camera->bounds.min     = {0.0f,    0.0f};
        camera->bounds.max     = {2000.0f, 1500.0f};

        camera->SetFollowMode<InstantFollow>();
    }
};


#endif //SDLPROJECT_GAMEPLAYSCENE_H
