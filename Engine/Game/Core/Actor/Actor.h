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

    virtual ~Actor() = default;

    Actor* parent = nullptr;
    std::vector<Actor*> children;

    Actor(){
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

    SDL_FRect GetBounds() const {
        Vector2 worldPos = GetWorldPosition();

        return {
                worldPos.x,
                worldPos.y,
                m_Transform->size.x,
                m_Transform->size.y
        };
    }

    template<typename T>
    T* AddComponent() {
        static_assert(std::is_base_of<Component, T>::value,
                      "T precisa herdar de Component");

        auto* component = new T();
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

    bool RemoveComponent(Component* component) {
        if(component == m_Transform) return false;

        auto it = std::find(m_Components.begin(), m_Components.end(), component);
        if(it != m_Components.end()){
            delete *it;
            m_Components.erase(it);

            return true;
        }

        return false;
    }

    void AddExistingComponent(Component* component) {
        component->owner = this;
        m_Components.push_back(component);
    }

    const std::vector<Component*>& GetComponents() const {
        return m_Components;
    }

    virtual void Update(float deltaTime) {
        for (auto* c : m_Components)
            c->Update(deltaTime);
    }

    virtual void Draw(SDL_Renderer* renderer) {
        for (auto* c : m_Components)
            c->Draw(renderer);
    }

    void SetActive(bool active)
    {
        m_IsActive = active;
    }

    bool IsActive() { return m_IsActive; }

private:
    std::vector<Component*> m_Components;
    Transform* m_Transform = nullptr;

    bool m_IsActive = true;
};

#endif //SDLPROJECT_ACTOR_H
