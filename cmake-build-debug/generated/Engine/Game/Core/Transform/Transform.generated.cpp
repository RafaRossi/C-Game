// DO NOT EDIT. Auto-generated.
#include "D:/Projetos/SDLProject/Engine/Game/Core/Transform/Transform.h"

#include "Engine/Game/Core/Factory/Factory.h"

#include "Engine/Game/Core/Reflection/PropertyType/PropertyType.h"

void Transform::AutoExposeField(FieldCollector& collector) {
    collector.Expose("position", &position);
    collector.Expose("rotation", &rotation);
    collector.Expose("scale", &scale);
}

static bool bReg_Transform = []() {
    Factory<Component>::Register("Transform", []() { return new Transform(); });
    return true;
}();
