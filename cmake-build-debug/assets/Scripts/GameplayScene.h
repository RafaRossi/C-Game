//
// Created by rossi on 11/07/2026.
//

#ifndef SDLPROJECT_GAMEPLAYSCENE_H
#define SDLPROJECT_GAMEPLAYSCENE_H


#include "Engine/Game/Core/Scene/Scene.h"
#include "Sandbox/Assets/Premades/Premades.h"
#include "Engine/Game/Core/Camera/Follow/LookAheadFollow.h"
#include "Engine/Game/Core/Camera/Follow/InstantFollow.h"
#include "Engine/Game/Core/Camera/Follow/SmoothFollow.h"

class GameplayScene : public Scene {

public:

    ~GameplayScene() = default;

    void InitializeScene() override {
        auto* playerActor = Premades::PlayerObject({ 0.f, 0.f }, 0);
        auto* weaponActor = Premades::GenericActor("Weapon", playerActor, playerActor->GetWorldPosition(), 0.f);

        (playerActor->GetComponent<Player>())->SetCurrentWeapon(weaponActor->AddComponent<WeaponComponent>());

        auto* camera = (CreateActor("Main Camera"))->AddComponent<CameraComponent>();
        SetMainCamera(camera);

        camera->followTarget  = true;
        camera->target        = playerActor->transform();

        camera->deadZone = {0.0f, 0.0f};

        camera->bounds.enabled = false;
        camera->bounds.min     = {0.0f,    0.0f};
        camera->bounds.max     = {2000.0f, 1500.0f};

        camera->SetFollowMode<SmoothFollow>();
    }
};


#endif //SDLPROJECT_GAMEPLAYSCENE_H
