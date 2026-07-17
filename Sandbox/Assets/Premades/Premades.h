//
// Created by rossi on 11/07/2026.
//

#ifndef SDLPROJECT_PREMADES_H
#define SDLPROJECT_PREMADES_H

#include <utility>

#include "Engine/Game/Core/Actor/Actor.h"
#include "Engine/Game/Core/Scene/Scene.h"
#include "Sandbox/Assets/Scripts/Player.h"
#include "Engine/Game/Core/Renderer/Renderer.h"
#include "Engine/Game/Core/RenderType/ShapeRender.h"
#include "Engine/Game/Core/Utils/DestroyActorAfterTime.h"
#include "Engine/Game/Core/Movement/ProjectileMovementComponent.h"

class Premades{
public:
    static Actor* PlayerObject(Vector2 position, float rotation){
        Actor* player = Game::Instance().CreateActor("Player");;
        player->AddComponent<Player>();
        auto* renderer = player->AddComponent<Renderer>();
        renderer->renderSize = { 40.f, 40.f };
        renderer->SetRenderType(new ShapeRender())->SetShape(new Square());

        player->transform()->position = position;
        player->transform()->rotation = rotation;

        return player;
    }

    static Actor* GenericActor(const std::string& actorName, Actor* parent, Vector2 position, float rotation){
        auto* actor = Game::Instance().CreateActor(actorName);

        actor->transform()->position = position;
        actor->transform()->rotation = rotation;

        parent->AddChild(actor);

        return actor;
    }

    static Actor* Bullet(Vector2 direction, float speed, Vector2 position, float rotation){

        auto* actor = Game::Instance().CreateActor("Bullet");

        auto* renderer = actor->AddComponent<Renderer>();
        renderer->renderSize = { 2.f, 2.f };
        (renderer->SetRenderType(new ShapeRender))->SetShape(new Square());

        (actor->AddComponent<DestroyActorAfterTime>())->StartTimer(3.f);

        auto* projMove = actor->AddComponent<ProjectileMovementComponent>();
        projMove->Shoot(direction, speed);

        actor->transform()->position = position;
        actor->transform()->rotation = rotation;

        return actor;
    }
};

#endif //SDLPROJECT_PREMADES_H
