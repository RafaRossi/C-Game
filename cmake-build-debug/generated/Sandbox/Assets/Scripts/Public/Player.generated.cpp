// DO NOT EDIT. Auto-generated.
#include "D:/Projetos/SDLProject/Sandbox/Assets/Scripts/Public/Player.h"

#include "Engine/Game/Core/Factory/Factory.h"

#include "Engine/Game/Core/Reflection/PropertyType/PropertyType.h"

void Player::AutoExposeField(FieldCollector& collector) {
}

static bool bReg_Player = []() {
    Factory<Component>::Register("Player", []() { return new Player(); });
    return true;
}();
