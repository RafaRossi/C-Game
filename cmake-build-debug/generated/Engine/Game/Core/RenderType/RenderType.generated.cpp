// DO NOT EDIT. Auto-generated.
#include "D:/Projetos/SDLProject/Engine/Game/Core/RenderType/RenderType.h"

#include "Engine/Editor/Factory/Factory.h"

#ifdef TR_EDITOR
void ShapeRenderer::AutoExposeField(FieldCollector& collector) {
    collector.Expose("teste", &teste);
}

static bool bReg_ShapeRenderer = []() {
    Factory<RenderType>::Register("ShapeRenderer", []() { return new ShapeRenderer(); });
    return true;
}();
#endif // TR_EDITOR
