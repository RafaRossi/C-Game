// DO NOT EDIT. Auto-generated.
#include "D:/Projetos/SDLProject/Sandbox/Assets/Scripts/WeaponComponent.h"

#include "Engine/Game/Core/Factory/Factory.h"

#include "Engine/Game/Core/Reflection/PropertyType/PropertyType.h"

void WeaponComponent::AutoExposeField(FieldCollector& collector) {
    collector.Expose("fireRate", &fireRate);
    collector.Expose("bulletSpeed", &bulletSpeed);
}

static bool bReg_WeaponComponent = []() {
    Factory<Component>::Register("WeaponComponent", []() { return new WeaponComponent(); });
    return true;
}();
