// DO NOT EDIT. Auto-generated.
#include "D:/Projetos/SDLProject/Sandbox/Assets/Scripts/Player.h"

#include "Engine/Game/Core/Factory/Factory.h"

#include "Engine/Game/Core/Reflection/PropertyType/PropertyType.h"

void Player::AutoExposeField(FieldCollector& collector) {
}

static bool bReg_Player = []() {
    Factory<Entity>::Register("Player", []() { return new Player(); });
    return true;
}();
