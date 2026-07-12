// DO NOT EDIT. Auto-generated.
#include "D:/Projetos/SDLProject/Engine/Game/Core/RenderType/ShapeRender.h"

#include "Engine/Game/Core/Factory/Factory.h"

#include "Engine/Game/Core/Reflection/PropertyType/PropertyType.h"

void ShapeRender::AutoExposeField(FieldCollector& collector) {
}

static bool bReg_ShapeRender = []() {
    Factory<RenderType>::Register("ShapeRender", []() { return new ShapeRender(); });
    return true;
}();
