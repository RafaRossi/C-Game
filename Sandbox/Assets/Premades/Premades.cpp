//
// Created by rossi on 21/07/2026.
//

#include "Premades.h"
#include "Engine/Game/Game.h"
#include "Sandbox/Assets/Scripts/Player.h"
#include "Engine/Game/Core/Renderer/Renderer.h"
#include "Engine/Game/Core/RenderType/ShapeRender.h"
#include "Engine/Game/Core/Shape/Shape.h"
#include "Engine/Game/Core/Utils/DestroyActorAfterTime.h"
#include "Engine/Game/Core/Movement/ProjectileMovementComponent.h"
#include "Engine/Game/Core/Rigidbody/Rigidbody.h"
#include "Engine/Game/Core/Collision/BoxCollider.h"

Actor *Premades::PlayerObject(Vector2 position, float rotation) {
    Actor* player = GenericActor("Player", nullptr, position, rotation);
    player->AddComponent<Player>();

    return player;
}

Actor *Premades::GenericActor(const std::string &actorName, Actor *parent, Vector2 position, float rotation) {
    auto* actor = Game::Instance().CreateActor(actorName);

    actor->transform()->position = position;
    actor->transform()->rotation = rotation;

    if(parent) parent->AddChild(actor);

    return actor;
}

Actor *Premades::Bullet(Vector2 direction, float speed, Vector2 position, float rotation) {
    auto* actor = Game::Instance().CreateActor("Bullet");
    actor->AddComponent<Renderer>(Color::White(), Vector2(5.f, 5.f));

    (actor->AddComponent<DestroyActorAfterTime>())->StartTimer(3.f);

    auto* rigidbody = actor->AddComponent<Rigidbody>(RigidbodyType::Dynamic);
    rigidbody->gravityScale = 0.f;
    rigidbody->linearDamping = 0.f;

    actor->AddComponent<BoxCollider>(rigidbody,Vector2(5.f, 5.f), true);

    auto* projMove = actor->AddComponent<ProjectileMovementComponent>(rigidbody);
    projMove->Shoot(direction, speed);

    actor->transform()->position = position;
    actor->transform()->rotation = rotation;

    return actor;
}