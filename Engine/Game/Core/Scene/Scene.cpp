//
// Created by rossi on 04/07/2026.
//

#include "Scene.h"

Scene::Scene(){
    m_Camera = nullptr;
}

Scene::~Scene(){
    for(auto* actor : m_PendingActors)
        delete actor;

    for(auto* actor : m_Actors)
        delete actor;

    m_Actors.clear();
}

Actor* Scene::CreateActor(const std::string& actorName) {
    auto* actor = new Actor(actorName);
    m_PendingActors.push_back(actor);
    m_LayerOrderDirty = true;

    m_sceneIsDirty = true;

    actor->OnCreated();

    return actor;
}

void Scene::Serialize() {
    m_Snapshot.clear();

    for (auto* actor : m_Actors) {
        ActorSnapshot snap;
        snap.name = actor->name;
        snap.position = actor->transform()->position;
        snap.scale     = actor->transform()->scale;
        snap.rotation = actor->transform()->rotation;
        snap.isActive = actor->IsActive();
        snap.layer    = actor->layer;

        m_Snapshot.push_back(snap);
    }
}

void Scene::Deserialize() {
    if (m_Snapshot.size() != m_Actors.size()) return;

    for (int i = 0; i < m_Actors.size(); i++) {
        m_Actors[i]->name = m_Snapshot[i].name;
        m_Actors[i]->transform()->position = m_Snapshot[i].position;
        m_Actors[i]->transform()->scale     = m_Snapshot[i].scale;
        m_Actors[i]->transform()->rotation = m_Snapshot[i].rotation;
        m_Actors[i]->SetActive(m_Snapshot[i].isActive);
        m_Actors[i]->layer                 = m_Snapshot[i].layer;
    }
}

Scene *SceneAsset::Instantiate() const {
    /*auto* runtimeScene = new Scene();

    SceneSerializer::LoadScene(runtimeScene, filePath);

    return runtimeScene;*/
    return nullptr;
}
