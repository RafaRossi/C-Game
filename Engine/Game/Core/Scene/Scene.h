//
// Created by rossi on 04/07/2026.
//

#ifndef SDLPROJECT_SCENE_H
#define SDLPROJECT_SCENE_H


#include <string>
#include "../Actor/Actor.h"
#include "../Camera/CameraComponent.h"
#include "Engine/Game/Core/Serialization/SceneSerializer/SceneSerializer.h"


class Scene {
public:
    std::string name;

    Scene();
    ~Scene();

    Actor* CreateActor(const std::string& actorName = "New Actor");
    std::vector<Actor*>& GetActors() { return m_Actors; }

    void ProcessPendingActors(){
        for (Actor* actor : m_PendingActors) {
            m_Actors.push_back(actor);
        }
        m_PendingActors.clear();
    }

    CameraComponent* GetCamera() const { return m_Camera; }


    void SetMainCamera(CameraComponent* cameraComponent) {
        if(m_Camera) m_Camera->SetMainCamera(false);

        m_Camera = cameraComponent;
        m_Camera->SetMainCamera(true);
    }

    bool IsLayerOrderDirty() const { return m_LayerOrderDirty; }
    void SetLayerOrderDirty(bool dirty) { m_LayerOrderDirty = dirty; }

    void Serialize();
    void Deserialize();

    virtual void InitializeScene() = 0;

private:
    CameraComponent* m_Camera = nullptr;
    std::vector<Actor*> m_Actors;
    std::vector<Actor*> m_PendingActors;

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
