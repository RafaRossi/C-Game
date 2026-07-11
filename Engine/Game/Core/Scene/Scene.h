//
// Created by rossi on 04/07/2026.
//

#ifndef SDLPROJECT_SCENE_H
#define SDLPROJECT_SCENE_H


#include <string>
#include "../Actor/Actor.h"
#include "../Camera/CameraComponent.h"
#include "Engine/Editor/SceneSerializer/SceneSerializer.h"


class Scene {
public:
    std::string name;

    Scene();
    ~Scene();

    Actor* CreateActor(const std::string& actorName = "New Actor");
    void RemoveActor(Actor* actor);
    std::vector<Actor*>& GetActors() { return m_Actors; }

    Actor* GetCameraActor() const { return m_CameraActor; }
    CameraComponent* GetCamera() const { return m_CameraActor->GetComponent<CameraComponent>(); }

    void SetMainCamera(CameraComponent* cameraComponent) {
        GetCamera()->SetMainCamera(false);
        m_CameraActor = cameraComponent->owner;
        GetCamera()->SetMainCamera(true);
    }

    bool IsLayerOrderDirty() const { return m_LayerOrderDirty; }
    void SetLayerOrderDirty(bool dirty) { m_LayerOrderDirty = dirty; }

    void Serialize();
    void Deserialize();

private:
    Actor* m_CameraActor = nullptr;
    std::vector<Actor*> m_Actors;

    bool m_LayerOrderDirty = true;
    bool m_sceneIsDirty = false;

    struct ActorSnapshot {
        std::string name;

        Vector2 position;
        Vector2 scale;

        float rotation;
        bool isActive;

        Layer layer;
    };

    std::vector<ActorSnapshot> m_Snapshot;
};

class SceneAsset{
public:
    std::string filePath;

    Scene* Instantiate() const;
};

#endif //SDLPROJECT_SCENE_H
