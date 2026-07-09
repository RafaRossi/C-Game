// DO NOT EDIT. Auto-generated.
#include "D:/Projetos/SDLProject/Engine/Game/Core/Transform/Transform.h"

#include "Engine/Editor/ComponentFactory/ComponentFactory.h"

#ifdef TR_EDITOR
void Transform::AutoExposeField(FieldCollector& collector) {
    collector.Expose("position", &position);
    collector.Expose("rotation", &rotation);
    collector.Expose("size", &size);
    collector.Expose("teste", &teste);
}

static bool bReg_Transform = []() {
    ComponentFactory::Register("Transform", []() { return new Transform(); });
    return true;
}();
#endif // TR_EDITOR
