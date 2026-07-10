// DO NOT EDIT. Auto-generated.
#include "D:/Projetos/SDLProject/Engine/Game/Core/Renderer/Renderer.h"

#include "Engine/Editor/Factory/Factory.h"

#ifdef TR_EDITOR
void Renderer::AutoExposeField(FieldCollector& collector) {
    collector.Expose("color", &color);
    collector.Expose("orderInLayer", &orderInLayer);
    collector.ExposePolymorphic<RenderType>("Render Type", &renderType);
}

static bool bReg_Renderer = []() {
    Factory<Component>::Register("Renderer", []() { return new Renderer(); });
    return true;
}();
#endif // TR_EDITOR
