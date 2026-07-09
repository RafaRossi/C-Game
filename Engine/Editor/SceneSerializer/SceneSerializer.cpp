#include "SceneSerializer.h"
#include "../ComponentFactory/ComponentFactory.h"
#include "Engine/ThirdParty/json.hpp"
#include "Engine/Game/Core/Actor/Actor.h"
#include <fstream>
#include <unordered_map>
#include "../../Game/Core/Scene/Scene.h"

using json = nlohmann::json;

void SceneSerializer::SaveScene(Scene* scene, const std::string& path) {
    std::filesystem::path filePath(path);
    if (filePath.has_parent_path()) {
        std::filesystem::create_directories(filePath.parent_path());
    }

    json root;
    root["actors"] = json::array();

    std::unordered_map<Actor*, int> actorToIdMap;
    int currentId = 1;

    for (auto* actor : scene->GetActors()) {
        actorToIdMap[actor] = currentId++;
    }

    for (auto* actor : scene->GetActors()) {
        json actorJson;
        actorJson["id"]     = actorToIdMap[actor];
        actorJson["parent_id"] = actor->parent ? actorToIdMap[actor->parent] : 0;

        actorJson["name"]   = actor->name;
        actorJson["layer"]  = (int)actor->layer;
        actorJson["active"] = actor->IsActive();
        actorJson["components"] = json::array();

        for (auto* component : actor->GetComponents()) {
            FieldCollector collector;
            component->AutoExposeField(collector);

            json compJson;
            compJson["class"] = component->GetComponentName();
            compJson["properties"] = json::object();

            for (const auto& field : collector.GetFields()) {
                switch (field.Type) {
                    case PropertyType::Int:
                        compJson["properties"][field.Name] = *static_cast<int*>(field.Ptr);
                        break;
                    case PropertyType::Float:
                        compJson["properties"][field.Name] = *static_cast<float*>(field.Ptr);
                        break;
                    case PropertyType::Bool:
                        compJson["properties"][field.Name] = *static_cast<bool*>(field.Ptr);
                        break;
                    case PropertyType::Vector2: {
                        auto* v = static_cast<Vector2*>(field.Ptr);
                        compJson["properties"][field.Name] = { v->x, v->y };
                        break;
                    }
                    case PropertyType::String:
                        compJson["properties"][field.Name] = *static_cast<std::string*>(field.Ptr);
                        break;
                }
            }
            actorJson["components"].push_back(compJson);
        }
        root["actors"].push_back(actorJson);
    }

    std::ofstream file(path);
    if (!file.is_open()) {
        return;
    }
    file << root.dump(4);
}

bool SceneSerializer::LoadScene(Scene* scene, const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return false;
    }

    json root;
    file >> root;

    std::unordered_map<int, Actor*> idToActorMap;

    for (const auto& actorJson : root["actors"]) {
        Actor* actor = scene->CreateActor();

        int actorId = actorJson.value("id", 0);
        idToActorMap[actorId] = actor;

        actor->name = actorJson.value("name", "Actor");
        actor->layer = (Layer)actorJson.value("layer", 0);
        actor->SetActive(actorJson.value("active", true));

        for (const auto& compJson : actorJson["components"]) {
            std::string className = compJson.value("class", "");
            if (className.empty()) continue;

            Component* component = nullptr;
            if (className == "Transform") {
                component = actor->transform();
            } else {
                component = ComponentFactory::Create(className);
                if (component == nullptr) continue;
                actor->AddComponent(component);
            }

            FieldCollector collector;
            component->AutoExposeField(collector);

            const auto& props = compJson["properties"];
            for (const auto& field : collector.GetFields()) {
                if (!props.contains(field.Name)) continue;

                switch (field.Type) {
                    case PropertyType::Int:
                        *static_cast<int*>(field.Ptr) = props[field.Name].get<int>();
                        break;
                    case PropertyType::Float:
                        *static_cast<float*>(field.Ptr) = props[field.Name].get<float>();
                        break;
                    case PropertyType::Bool:
                        *static_cast<bool*>(field.Ptr) = props[field.Name].get<bool>();
                        break;
                    case PropertyType::Vector2: {
                        auto arr = props[field.Name].get<std::vector<float>>();
                        if (arr.size() == 2)
                            *static_cast<Vector2*>(field.Ptr) = { arr[0], arr[1] };
                        break;
                    }
                    case PropertyType::String:
                        *static_cast<std::string*>(field.Ptr) = props[field.Name].get<std::string>();
                        break;
                }
            }
        }
    }

    for (const auto& actorJson : root["actors"]) {
        int actorId = actorJson.value("id", 0);
        int parentId = actorJson.value("parent_id", 0);

        if (parentId != 0) {
            Actor* child = idToActorMap[actorId];
            Actor* parent = idToActorMap[parentId];

            if (parent && child) {
                parent->AddChild(child);
            }
        }
    }

    return true;
}