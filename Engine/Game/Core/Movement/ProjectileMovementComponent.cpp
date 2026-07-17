//
// Created by rossi on 13/07/2026.
//
#include "ProjectileMovementComponent.h"
#include "../Actor/Actor.h"

void ProjectileMovementComponent::Update(float deltaTime) {

    Vector2 currentPos = owner->transform()->position;

    currentPos = currentPos + (direction * speed * deltaTime);

    owner->transform()->position = currentPos;
}