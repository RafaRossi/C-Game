//
// Created by rossi on 17/07/2026.
//

#ifndef SDLPROJECT_RIGIDBODY_H
#define SDLPROJECT_RIGIDBODY_H

#include "Engine/Game/Core/Component/Component.h"
#include "box2d/box2d.h"

enum class RigidbodyType
{
    Dynamic,
    Kinematic,
    Static
};

class Rigidbody : public Component{
    REGISTER_BODY(Rigidbody, Component)

private:
    b2Body* m_Body = nullptr;
    RigidbodyType m_RigidbodyType;

public:

    void SetRigidbodyType(RigidbodyType rigidbodyType);
};

#endif //SDLPROJECT_RIGIDBODY_H
