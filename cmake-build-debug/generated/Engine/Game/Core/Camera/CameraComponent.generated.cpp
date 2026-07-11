// DO NOT EDIT. Auto-generated.
#include "D:/Projetos/SDLProject/Engine/Game/Core/Camera/CameraComponent.h"

#include "Engine/Editor/Factory/Factory.h"

#ifdef TR_EDITOR
void CameraComponent::AutoExposeField(FieldCollector& collector) {
    collector.Expose("m_IsMainCamera", &m_IsMainCamera);
}

static bool bReg_CameraComponent = []() {
    Factory<Component>::Register("CameraComponent", []() { return new CameraComponent(); });
    return true;
}();
#endif // TR_EDITOR
