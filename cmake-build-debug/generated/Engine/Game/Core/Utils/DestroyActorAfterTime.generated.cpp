// DO NOT EDIT. Auto-generated.
#include "D:/Projetos/SDLProject/Engine/Game/Core/Utils/DestroyActorAfterTime.h"

#include "Engine/Game/Core/Factory/Factory.h"

#include "Engine/Game/Core/Reflection/PropertyType/PropertyType.h"

void DestroyActorAfterTime::AutoExposeField(FieldCollector& collector) {
}

static bool bReg_DestroyActorAfterTime = []() {
    Factory<Component>::Register("DestroyActorAfterTime", []() { return new DestroyActorAfterTime(); });
    return true;
}();
