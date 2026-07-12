// DO NOT EDIT. Auto-generated.
#include "D:/Projetos/SDLProject/Engine/Game/Core/Renderer/Renderer.h"

#include "Engine/Game/Core/Factory/Factory.h"

#include "Engine/Game/Core/Reflection/PropertyType/PropertyType.h"

void Renderer::AutoExposeField(FieldCollector& collector) {
    collector.Expose("color", &color);
    collector.Expose("orderInLayer", &orderInLayer);
    collector.Expose("renderSize", &renderSize);
    collector.ExposePolymorphic<RenderType>("Render Type", &renderType);
}

static bool bReg_Renderer = []() {
    Factory<Component>::Register("Renderer", []() { return new Renderer(); });
    return true;
}();
