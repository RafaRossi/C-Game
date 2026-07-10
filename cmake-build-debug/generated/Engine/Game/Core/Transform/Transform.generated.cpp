// DO NOT EDIT. Auto-generated.
#include "D:/Projetos/SDLProject/Engine/Game/Core/Transform/Transform.h"

#include "Engine/Editor/Factory/Factory.h"

#ifdef TR_EDITOR
void Transform::AutoExposeField(FieldCollector& collector) {
    collector.Expose("position", &position);
    collector.Expose("rotation", &rotation);
    collector.Expose("scale", &scale);
}

static bool bReg_Transform = []() {
    Factory<Component>::Register("Transform", []() { return new Transform(); });
    return true;
}();
#endif // TR_EDITOR
