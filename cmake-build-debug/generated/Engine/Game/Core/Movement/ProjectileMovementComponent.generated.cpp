// DO NOT EDIT. Auto-generated.
#include "D:/Projetos/SDLProject/Engine/Game/Core/Movement/ProjectileMovementComponent.h"

#include "Engine/Game/Core/Factory/Factory.h"

#include "Engine/Game/Core/Reflection/PropertyType/PropertyType.h"

void ProjectileMovementComponent::AutoExposeField(FieldCollector& collector) {
    collector.Expose("direction", &direction);
    collector.Expose("speed", &speed);
}

static bool bReg_ProjectileMovementComponent = []() {
    Factory<Component>::Register("ProjectileMovementComponent", []() { return new ProjectileMovementComponent(); });
    return true;
}();
