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
#include "Engine/Game/Core/Rigidbody/Rigidbody.h"
#include "Engine/Game/Core/Movement/ProjectileMovementComponent.h"
#include "Engine/Game/Core/Collision/BoxCollider.h"

class Premades{
public:
    static Actor* PlayerObject(Vector2 position, float rotation){
        Actor* player = Game::Instance().CreateActor("Player");;
        player->AddComponent<Player>();

        player->transform()->position = position;
        player->transform()->rotation = rotation;

        auto* rigidbody = player->AddComponent<Rigidbody>();
        rigidbody->SetRigidbodyType(RigidbodyType::Dynamic);
        rigidbody->gravityScale = 0.f;

        Actor* collider = GenericActor("Collider", player, player->GetWorldPosition(), player->GetWorldRotation());

        auto* boxCollider = collider->AddComponent<BoxCollider>();
        boxCollider->size = { 40.f, 40.f};

        auto* r = collider->AddComponent<Renderer>();
        r->SetRenderSize({ 40.f, 40.f} );
        r->SetRenderType(new ShapeRender())->SetShape(new Square());

        Actor* visual = GenericActor("Visual", player, player->GetWorldPosition(), player->GetWorldRotation());

        auto* renderer = visual->AddComponent<Renderer>();
        renderer->SetRenderSize( {40.f, 40.f } );
        renderer->SetRenderType(new ShapeRender())->SetShape(new Square());

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
        renderer->SetRenderSize( {2.f, 2.f } );
        renderer->SetRenderType(new ShapeRender)->SetShape(new Square());


        (actor->AddComponent<DestroyActorAfterTime>())->StartTimer(3.f);

        auto* projMove = actor->AddComponent<ProjectileMovementComponent>();
        projMove->Shoot(direction, speed);

        actor->transform()->position = position;
        actor->transform()->rotation = rotation;

        return actor;
    }
};

#endif //SDLPROJECT_PREMADES_H
