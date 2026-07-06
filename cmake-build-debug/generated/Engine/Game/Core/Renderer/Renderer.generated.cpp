// DO NOT EDIT. Auto-generated.
#include "D:/Projetos/SDLProject/Engine/Game/Core/Renderer/Renderer.h"

#include "Engine/Editor/ComponentFactory/ComponentFactory.h"

#ifdef TR_EDITOR
void Renderer::AutoExposeField(FieldCollector& collector) {
}

static bool bReg_Renderer = []() {
    ComponentFactory::Register("Renderer", []() { return new Renderer(); });
    return true;
}();
#endif // TR_EDITOR
