// DO NOT EDIT. Auto-generated.
#include "D:/Projetos/SDLProject/Engine/Game/Core/RenderType/ShapeRender.h"

#include "Engine/Editor/Factory/Factory.h"

#ifdef TR_EDITOR
void ShapeRender::AutoExposeField(FieldCollector& collector) {
    collector.ExposePolymorphic<Shape>("shape", &shape);
}

static bool bReg_ShapeRender = []() {
    Factory<RenderType>::Register("ShapeRender", []() { return new ShapeRender(); });
    return true;
}();
#endif // TR_EDITOR
