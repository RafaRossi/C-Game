//
// Created by rossi on 11/07/2026.
//

#ifndef SDLPROJECT_PREMADES_H
#define SDLPROJECT_PREMADES_H

#include "Engine/Game/Core/Actor/Actor.h"
#include "Engine/Game/Core/Scene/Scene.h"
#include "Sandbox/Assets/Scripts/Player.h"
#include "Engine/Game/Core/Renderer/Renderer.h"
#include "Engine/Game/Core/RenderType/ShapeRender.h"

class Premades{
public:
    static Actor* PlayerObject(Scene* scene, Vector2 position, float rotation){
        Actor* player = scene->CreateActor("Player");
        player->AddComponent<Player>();
        auto* renderer = player->AddComponent<Renderer>();
        renderer->SetRenderType(new ShapeRender())->SetShape(new Square());

        player->transform()->position = position;
        player->transform()->rotation = rotation;

        return player;
    }
};

#endif //SDLPROJECT_PREMADES_H
