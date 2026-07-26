//
// Created by rossi on 17/07/2026.
//
#include "Player.h"
#include "Engine/Game/Game.h"
#include "Engine/Game/Core/Rigidbody/Rigidbody.h"
#include "Sandbox/Assets/Premades/Premades.h"
#include "Engine/Game/Core/Collision/BoxCollider.h"
#include "Engine/Game/Core/Renderer/Renderer.h"
#include "Engine/Game/Core/RenderType/ShapeRender.h"

Player::Player(Actor *actor) {
    SetBaseStat(Stats::Speed, 500.f);
    SetBaseStat(Stats::AttackSpeed, .5f);

    auto* weaponActor = Premades::GenericActor("Weapon", actor, actor->GetWorldPosition(), 0.f);

    auto* weaponComponent = weaponActor->AddComponent<WeaponComponent>();
    SetWeaponComponent(weaponComponent);

    auto weapon = new ProjectileGun(this);
    weaponComponent->AddWeapon(weapon);

    auto weapon2 = new ProjectileGun(this, 1.f);
    weaponComponent->AddWeapon(weapon2);

    auto* rigidbody = actor->AddComponent<Rigidbody>(RigidbodyType::Dynamic);
    rigidbody->gravityScale = 0.f;

    Actor* collider = Premades::GenericActor("Collider", actor, actor->GetWorldPosition(), actor->GetWorldRotation());
    collider->AddComponent<BoxCollider>(rigidbody, Vector2(40.f, 40.f));

    Actor* visual = Premades::GenericActor("Visual", actor, actor->GetWorldPosition(), actor->GetWorldRotation());

    auto* renderer = visual->AddComponent<Renderer>(Color::Blue(), Vector2(40.f, 40.f));
    renderer->SetRenderType(new ShapeRender())->SetShape(new Square());
}

void Player::Update(float deltaTime) {
    auto moveInput = InputManager::Instance().GetAxis2D(SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_W, SDL_SCANCODE_S).Normalized();

    auto* rigidbody = owner->GetComponent<Rigidbody>();

    if (rigidbody != nullptr) {
        Vector2 targetVelocity = moveInput * GetStat(Stats::Speed);

        rigidbody->SetVelocity(targetVelocity);
    }

    if(InputManager::Instance().IsMouseButtonDown(1) && m_Weapon){

        Vector2 screenMousePos = InputManager::Instance().GetMousePosition();
        Vector2 targetWorldPos = Game::Instance().GetScene()->GetCamera()->ScreenToWorld(screenMousePos);

        m_Weapon->TryShoot(this, targetWorldPos);
    }

    if (m_ScrollCooldown > 0.0f) {
        m_ScrollCooldown -= deltaTime;
    }

    float scroll = InputManager::Instance().GetMouseScroll();

    if (scroll != 0.0f && m_ScrollCooldown <= 0.0f) {

        if (scroll > 0) {
            m_Weapon->EquipNextWeapon();
        }
        else if (scroll < 0) {
            m_Weapon->EquipPreviousWeapon();
        }

        m_ScrollCooldown = SCROLL_DELAY;
    }
}
