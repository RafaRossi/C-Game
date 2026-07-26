//
// Created by rossi on 11/07/2026.
//

#ifndef SDLPROJECT_GAMEPLAYSCENE_H
#define SDLPROJECT_GAMEPLAYSCENE_H


#include "Engine/Game/Core/Scene/Scene.h"

class GameplayScene : public Scene {

public:

    ~GameplayScene() = default;

    void InitializeScene() override;
};


#endif //SDLPROJECT_GAMEPLAYSCENE_H
