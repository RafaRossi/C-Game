// DO NOT EDIT. Auto-generated.
#include "D:/Projetos/SDLProject/Engine/Game/Core/Camera/CameraComponent.h"

#include "Engine/Game/Core/Factory/Factory.h"

#include "Engine/Game/Core/Reflection/PropertyType/PropertyType.h"

void CameraComponent::AutoExposeField(FieldCollector& collector) {
    collector.Expose("zoom", &zoom);
    collector.Expose("backgroundColor", &backgroundColor);
    collector.Expose("followTarget", &followTarget);
    collector.ExposePolymorphic<Transform>("target", &target);
    collector.Expose("smoothSpeed", &smoothSpeed);
    collector.Expose("m_IsMainCamera", &m_IsMainCamera);
}

static bool bReg_CameraComponent = []() {
    Factory<Component>::Register("CameraComponent", []() { return new CameraComponent(); });
    return true;
}();
