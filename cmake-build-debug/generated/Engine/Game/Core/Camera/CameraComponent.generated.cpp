// DO NOT EDIT. Auto-generated.
#include "D:/Projetos/SDLProject/Engine/Game/Core/Camera/CameraComponent.h"

#include "Engine/Editor/ComponentFactory/ComponentFactory.h"

#ifdef TR_EDITOR
void CameraComponent::AutoExposeField(FieldCollector& collector) {
}

static bool bReg_CameraComponent = []() {
    ComponentFactory::Register("CameraComponent", []() { return new CameraComponent(); });
    return true;
}();
#endif // TR_EDITOR
