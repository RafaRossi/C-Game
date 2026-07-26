//
// Created by rossi on 25/07/2026.
//

#include "GameplayScene.h"
#include "Sandbox/Assets/Premades/Premades.h"
#include "Engine/Game/Core/Renderer/Renderer.h"
#include "Engine/Game/Core/Camera/Follow/InstantFollow.h"
#include "Engine/Game/Core/Collision/BoxCollider.h"

void GameplayScene::InitializeScene() {
    auto* playerActor = Premades::PlayerObject({ 0.f, 0.f }, 0);

    auto* camera = (CreateActor("Main Camera"))->AddComponent<CameraComponent>();
    SetMainCamera(camera);

    //TODO Fazer um script que carrega um map com base em um mapa de cores
    auto* wall = Premades::GenericActor("Wall", nullptr, {100.f, 0.f}, 0.f);
    Vector2 size = Vector2(100, 500);

    wall->AddComponent<Renderer>(Color::Amber(), size);
    wall->AddComponent<BoxCollider>();

    camera->followTarget  = true;
    camera->target        = playerActor->transform();

    camera->deadZone      = {0.0f, 0.0f};

    camera->bounds.enabled = false;
    camera->bounds.min     = {0.0f,    0.0f};
    camera->bounds.max     = {2000.0f, 1500.0f};

    camera->SetFollowMode<InstantFollow>();
}

