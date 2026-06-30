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
#include "../Renderer/Renderer.h"

struct Transform {
    Vector2 position;
    float rotation = 0.0f;
    Vector2 size = { 100.f, 100.f};

    SDL_FRect GetBounds(Vector2 worldPosition) const {
        return {
                worldPosition.x,
                worldPosition.y,
                size.x,
                size.y
        };
    }
};


struct Actor {
    Transform transform;
    Renderer renderer;

    Actor* parent = nullptr;
    std::vector<Actor*> children;

public:

    void Draw(SDL_Renderer* renderer) const;
    void Update(float deltaTime);

    Vector2 GetWorldPosition() const {
        if(parent == nullptr)
            return transform.position;

        return parent->GetWorldPosition() + transform.position;
    }

    float GetWorldRotation() const {
        if(parent == nullptr)
            return transform.rotation;

        return parent->GetWorldRotation() + transform.rotation;
    }

    void AddChild(Actor* child){
        if(child == nullptr || child == this) return;

        if(child->parent == this) return;

        if(child->parent != nullptr) child->parent->RemoveChild(child);

        child->parent = this;
        children.push_back(child);
    }

    void RemoveChild(Actor* child){
        auto it = std::find(children.begin(), children.end(), child);
        if(it != children.end()){
            (*it)->parent = nullptr;
            children.erase(it);
        }
    }
};

#endif //SDLPROJECT_ACTOR_H
