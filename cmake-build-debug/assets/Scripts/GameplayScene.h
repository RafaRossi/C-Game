//
// Created by rossi on 11/07/2026.
//

#ifndef SDLPROJECT_GAMEPLAYSCENE_H
#define SDLPROJECT_GAMEPLAYSCENE_H


#include "Engine/Game/Core/Scene/Scene.h"
#include "Engine/Game/Core/Premades/Premades.h"

class GameplayScene : public Scene {

public:

    ~GameplayScene() = default;

    void InitializeScene() override {
        auto* camera = (CreateActor())->AddComponent<CameraComponent>();
        SetMainCamera(camera);

        auto* playerActor = Premades::PlayerObject(this, { 0.f, 0.f }, 0);

        camera->followTarget  = true;
        camera->target        = playerActor->transform();
        camera->smoothSpeed   = 5.0f;

        camera->deadZone = {0.0f, 0.0f};

        camera->bounds.enabled = true;
        camera->bounds.min     = {0.0f,    0.0f};
        camera->bounds.max     = {2000.0f, 1500.0f};
    }
};


#endif //SDLPROJECT_GAMEPLAYSCENE_H
