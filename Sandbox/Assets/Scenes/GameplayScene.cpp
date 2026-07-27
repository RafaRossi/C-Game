//
// Created by rossi on 25/07/2026.
//

#include "GameplayScene.h"
#include "Sandbox/Assets/Premades/Premades.h"
#include "Engine/Game/Core/Camera/Follow/InstantFollow.h"
#include "LevelRoom.h"

void GameplayScene::InitializeScene() {

    auto* camera = (CreateActor("Main Camera"))->AddComponent<CameraComponent>();
    SetMainCamera(camera);

    auto* level = new Level();
    level->GenerateLevel("../Sandbox/Assets/Scenes/Level_Test.bmp");

    auto spawnPoint = Game::GetRandomElement<Vector2>(level->PlayerSpawnPoints()).value_or(Vector2(0.f, 0.f));

    auto* playerActor = Premades::PlayerObject(spawnPoint, 0);

    camera->followTarget  = true;
    camera->target        = playerActor->transform();

    camera->deadZone      = {0.0f, 0.0f};

    camera->bounds.enabled = false;
    camera->bounds.min     = {0.0f,    0.0f};
    camera->bounds.max     = {static_cast<float>(level->Width()), static_cast<float>(level->Height())};

    camera->SetFollowMode<InstantFollow>();
}

