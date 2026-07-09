//
// Created by rossi on 04/07/2026.
//

#include "Scene.h"

Scene::Scene(){

}

Scene::~Scene(){
    for(auto* actor : m_Actors)
        delete actor;

    m_Actors.clear();
}

Actor* Scene::CreateActor(const std::string& actorName) {
    auto* actor = new Actor(actorName);
    m_Actors.push_back(actor);
    m_LayerOrderDirty = true;
    return actor;
}

void Scene::RemoveActor(Actor* actor) {
    if (actor == nullptr) return;

    for (auto* child : actor->children)
    {
        RemoveActor(child);
    }

    if (actor->parent != nullptr)
        actor->parent->RemoveChild(actor);

    auto it = std::find(m_Actors.begin(), m_Actors.end(), actor);
    if (it != m_Actors.end()) {
        delete *it;
        m_Actors.erase(it);
        m_LayerOrderDirty = true;
    }
}

void Scene::Serialize() {
    m_Snapshot.clear();

    for (auto* actor : m_Actors) {
        ActorSnapshot snap;
        snap.name = actor->name;
        snap.position = actor->transform()->position;
        snap.size     = actor->transform()->size;
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
        m_Actors[i]->transform()->size     = m_Snapshot[i].size;
        m_Actors[i]->transform()->rotation = m_Snapshot[i].rotation;
        m_Actors[i]->SetActive(m_Snapshot[i].isActive);
        m_Actors[i]->layer                 = m_Snapshot[i].layer;
    }
}

Scene *SceneAsset::Instantiate() const {
    auto* runtimeScene = new Scene();

    SceneSerializer::LoadScene(runtimeScene, filePath);

    return runtimeScene;
}
