// DO NOT EDIT. Auto-generated.
#include "D:/Projetos/SDLProject/Sandbox/Assets/Scripts/Entity.h"

#include "Engine/Game/Core/Factory/Factory.h"

#include "Engine/Game/Core/Reflection/PropertyType/PropertyType.h"

void Entity::AutoExposeField(FieldCollector& collector) {
}

static bool bReg_Entity = []() {
    Factory<Component>::Register("Entity", []() { return new Entity(); });
    return true;
}();
