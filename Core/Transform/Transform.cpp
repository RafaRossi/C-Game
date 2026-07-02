//
// Created by rossi on 02/07/2026.
//

#include "Transform.h"
#include "../Reflection/Reflection.h"

BEGIN_REFLECTION(Transform)
    PROPERTY(Transform, Vector2, position)
    PROPERTY(Transform, Float, rotation)
    PROPERTY(Transform, Vector2, size)
END_REFLECTION(Transform)