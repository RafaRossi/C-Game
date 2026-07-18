//
// Created by rossi on 17/07/2026.
//

#ifndef SDLPROJECT_BOXCOLLIDER_H
#define SDLPROJECT_BOXCOLLIDER_H


#include "Collider.h"
#include "Engine/Game/Core/Rigidbody/Rigidbody.h"

class BoxCollider : public Collider {
    REGISTER_BODY(BoxCollider, Collider)

public:
    ~BoxCollider() override = default;

    void Start() override;

    Vector2 size = { 100.f, 100.f };

private:
    Rigidbody* m_Rigidbody;
    b2PolygonShape boxShape;
};

#endif //SDLPROJECT_BOXCOLLIDER_H
