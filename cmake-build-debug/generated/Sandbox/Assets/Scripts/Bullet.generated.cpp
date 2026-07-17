// DO NOT EDIT. Auto-generated.
#include "D:/Projetos/SDLProject/Sandbox/Assets/Scripts/Bullet.h"

#include "Engine/Game/Core/Factory/Factory.h"

#include "Engine/Game/Core/Reflection/PropertyType/PropertyType.h"

void Bullet::AutoExposeField(FieldCollector& collector) {
}

static bool bReg_Bullet = []() {
    Factory<Component>::Register("Bullet", []() { return new Bullet(); });
    return true;
}();
