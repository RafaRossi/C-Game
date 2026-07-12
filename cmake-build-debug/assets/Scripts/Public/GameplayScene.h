//
// Created by rossi on 11/07/2026.
//

#ifndef SDLPROJECT_GAMEPLAYSCENE_H
#define SDLPROJECT_GAMEPLAYSCENE_H


#include "Engine/Game/Core/Scene/Scene.h"
#include "Engine/Game/Core/Premades/Premades.h"

class GameplayScene : public Scene {

public:
    GameplayScene(){
        SetMainCamera((new Actor())->AddComponent<CameraComponent>());
        Premades::PlayerObject(this, { 0.f, 0.f }, 0);
    }

    ~GameplayScene() = default;
};


#endif //SDLPROJECT_GAMEPLAYSCENE_H
