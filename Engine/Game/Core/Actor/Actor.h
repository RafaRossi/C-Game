//
// Created by rossi on 29/06/2026.
//

#ifndef SDLPROJECT_ACTOR_H
#define SDLPROJECT_ACTOR_H

#include <vector>

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include "../Math/Vector2.h"
#include "../Component/Component.h"
#include "../Layer/Layer.h"
#include "../Transform/Transform.h"

class Actor {
public:
    std::string name;
    Transform* transform() const { return m_Transform; }
    Layer layer = Layer::Default;

    virtual ~Actor() {
        if(parent){
            parent->RemoveChild(this);
        }

        for (auto* component : m_Components) {
            delete component;
        }
        m_Components.clear();
    }

    Actor* parent = nullptr;
    std::vector<Actor*> children;

    explicit Actor(const std::string& actorName = "New Actor"){
        name = actorName;
        m_Transform = AddComponent<Transform>();
    }

    void AddChild(Actor* child) {
        if (child == nullptr || child == this) return;
        if (child->parent == this) return;

        if (child->parent != nullptr)
            child->parent->RemoveChild(child);

        child->parent = this;
        children.push_back(child);
    }

    void RemoveChild(Actor* child) {
        auto it = std::find(children.begin(), children.end(), child);
        if (it != children.end()) {
            (*it)->parent = nullptr;
            children.erase(it);
        }
    }

    Vector2 GetWorldPosition() const {
        if (parent == nullptr)
            return m_Transform->position;
        return parent->GetWorldPosition() + m_Transform->position;
    }

    float GetWorldRotation() const {
        if (parent == nullptr)
            return m_Transform->rotation;
        return parent->GetWorldRotation() + m_Transform->rotation;
    }

    template<typename T, typename... Args>
    T* AddComponent(Args&&... args) {
        static_assert(std::is_base_of<Component, T>::value,
                      "T is not a component.");

        T* component = nullptr;

        if constexpr (std::is_constructible_v<T, Actor*, Args...>) {
            component = new T(this, std::forward<Args>(args)...);
        }
        else if constexpr (sizeof...(Args) == 0 && std::is_default_constructible_v<T>) {
            component = new T();
        }
        else {
            static_assert(std::is_constructible_v<T, Actor*, Args...> || (sizeof...(Args) == 0 && std::is_default_constructible_v<T>),
                          "Component does not have a valid constructor matching the arguments.");
        }

        if (component->IsUnique() && HasComponent(component->GetTypeName())) {
            delete component;
            return nullptr;
        }

        if (component->owner == nullptr) {
            component->owner = this;
        }

        m_Components.push_back(component);

        return component;
    }

    Component* AddComponent(Component* component){
        if(!component) return nullptr;

        if(component->IsUnique() && HasComponent(component->GetTypeName())){
            delete component;
            return nullptr;
        }

        component->owner = this;
        m_Components.push_back(component);

        return component;
    }

    template<typename T>
    T* GetComponent() const {
        for (auto* c : m_Components)
            if (auto* casted = dynamic_cast<T*>(c))
                return casted;
        return nullptr;
    }

    bool HasComponent(const std::string& className) const {
        for (auto* comp : m_Components) {
            if (comp->GetTypeName() == className) return true;
        }
        return false;
    }

    template<typename T>
    bool HasComponent() const {
        static_assert((std::is_base_of<Component, T>::value, "T is not a component."));
        for (auto *comp: m_Components)
            if (dynamic_cast<T *>(comp) != nullptr) {
                return true;
            }

        return false;
    }

    bool RemoveComponent(Component* component) {
        if(!component->CanBeRemoved()) return false;

        auto it = std::find(m_Components.begin(), m_Components.end(), component);
        if(it != m_Components.end()){
            delete *it;
            m_Components.erase(it);

            return true;
        }

        return false;
    }

    const std::vector<Component*>& GetComponents() const {
        return m_Components;
    }

    virtual void Start() {
        for (auto* c : m_Components)
        {
            if(c->hasStarted) return;

            c->Start();
            c->hasStarted = true;
        }
    }

    virtual void Update(float deltaTime) {
        for (auto* c : m_Components){
            if (!c->hasStarted) {
                c->Start();
                c->hasStarted = true;
            }

            c->Update(deltaTime);
        }
    }

    virtual void LateUpdate(float deltaTime) {
        for (auto* c : m_Components)
            c->LateUpdate(deltaTime);
    }

    void SetActive(bool active)
    {
        m_IsActive = active;

        if(m_IsActive){
            OnEnabled();
        }
        else{
            OnDisabled();
        }
    }

    bool IsActive() const { return m_IsActive; }

    virtual void OnEnabled() { };
    virtual void OnDisabled() { };

    virtual void OnCreated() { };


    void Destroy(){
        if(m_IsPendingDestroy) return;

        m_IsPendingDestroy = true;
        SetActive(false);

        for (auto* child : children) {
            if(child)
            {
                child->Destroy();
            }
        }
    }

    bool IsPendingDestroy() const {
        return m_IsPendingDestroy;
    }

private:
    std::vector<Component*> m_Components;
    Transform* m_Transform = nullptr;

    bool m_IsActive = true;

    bool m_IsPendingDestroy = false;
};

#endif //SDLPROJECT_ACTOR_H
