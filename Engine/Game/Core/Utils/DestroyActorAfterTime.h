//
// Created by rossi on 14/07/2026.
//

#ifndef SDLPROJECT_DESTROYACTORAFTERTIME_H
#define SDLPROJECT_DESTROYACTORAFTERTIME_H

#include "Engine/Game/Core/Component/Component.h"
#include "Engine/Game/Core/Actor/Actor.h"
#include "Engine/Game/Game.h"

class DestroyActorAfterTime : public Component{
    REGISTER_BODY(DestroyActorAfterTime, Component)

public:
    void Update(float deltaTime) override {
        m_CurrentTime += deltaTime;

        if(m_CurrentTime >= m_Timer)
        {
            owner->Destroy();

            return;
        }
    }

    void StartTimer(float time) { m_Timer = time; }

private:
    float m_Timer = 0.f;
    float m_CurrentTime = 0.f;
};

#endif //SDLPROJECT_DESTROYACTORAFTERTIME_H
