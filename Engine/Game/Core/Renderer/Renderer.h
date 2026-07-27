//
// Created by rossi on 29/06/2026.
//

#ifndef SDLPROJECT_RENDERER_H
#define SDLPROJECT_RENDERER_H


#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include "../Component/Component.h"
#include "../Actor/Actor.h"
#include "Engine/Game/Core/RenderType/RenderType.h"
#include "../../Game.h"
#include "Engine/Game/Core/RenderType/ShapeRender.h"
#include "Engine/Game/Core/Shape/Shape.h"
#include "Sandbox/Assets/Scripts/Player.h"

class Renderer : public Component {
REGISTER_BODY(Renderer, Component)

public:
    PROPERTY() int orderInLayer = 0;

    Renderer() = default;
    explicit Renderer(Actor* owner, Color color = Color::White(), Vector2 size = {100, 100}, int orderInLayer = 0, RenderType* renderType = new ShapeRender(new Square()))
            : Component(owner), m_Color(color), m_RenderSize(size), m_RenderType(renderType), orderInLayer(orderInLayer) {}

    ~Renderer() override = default;

private:
    PROPERTY() Color m_Color = Color::White();
    PROPERTY() Vector2 m_RenderSize = {100, 100};
    PROPERTY(DisplayName = "Render Type") RenderType* m_RenderType = new ShapeRender(new Square());

public:

    void SetRenderSize(Vector2 size)
    {
        m_RenderSize = size;
    }

    void SetColor(Color color)
    {
        m_Color = color;
    }

    void Draw() {
        if(m_RenderType){
            m_RenderType->Draw(Game::Instance().GetRenderer(), GetBounds(owner->GetWorldPosition(), m_RenderSize), m_Color);
        }
    }

    template<typename T>
    T* SetRenderType(T* type)
    {
        static_assert(std::is_base_of_v<RenderType, T>, "T is not a RenderType.");

        m_RenderType = type;

        return type;
    }

    SDL_FRect GetBounds(Vector2 worldPosition, Vector2 size) const {
        CameraComponent* mainCamera = Game::Instance().GetScene()->GetCamera();

        Vector2 drawPos = worldPosition;

        if (mainCamera != nullptr) {
            drawPos = mainCamera->WorldToScreen(worldPosition);

        }

        return {
                drawPos.x - (size.x / 2.0f),
                drawPos.y - (size.y / 2.0f),
                size.x,
                size.y
        };
    }

    /*SDL_Texture* sprite = nullptr;
     void Draw(SDL_Renderer* renderer) override {
        auto bounds = owner->GetBounds();

        SDL_Color sdlColor = color.ToSDLColor();

        if(sprite != nullptr){
            SetTextureAlphaMod(sprite, sdlColor.a);
            SetTextureColorMod(sprite, sdlColor);
            SetRendererTexture(renderer, sprite, nullptr, &bounds);
        } else {
            SetRenderDrawColor(renderer, sdlColor);
            SetRenderFillRect(renderer, &bounds);
        }
    }*/

    static bool SetRenderDrawColor(SDL_Renderer* renderer, const SDL_Color color){
        return SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    }

    static bool SetRenderDrawColor(SDL_Renderer* renderer, const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a){
        return SDL_SetRenderDrawColor(renderer, r, g, b, a);
    }

    static bool SetRenderDrawColor(SDL_Renderer* renderer, Color32 color){
        return SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    }

    static bool SetRenderFillRect(SDL_Renderer* renderer, const SDL_FRect* bounds)
    {
        return SDL_RenderFillRect(renderer, bounds);
    }

    static bool SetTextureColorMod(SDL_Texture* sprite, const SDL_Color color){
        return SDL_SetTextureColorMod(sprite, color.r, color.g, color.b);
    }

    static bool SetRendererTexture(SDL_Renderer* renderer, SDL_Texture* sprite, const SDL_FRect* srcrect, const SDL_FRect* dstrect){
        return SDL_RenderTexture(renderer, sprite, srcrect, dstrect);
    }

    static bool SetTextureAlphaMod(SDL_Texture* sprite, Uint8 alpha){
        return SDL_SetTextureAlphaMod(sprite, alpha);
    }
};

#endif //SDLPROJECT_RENDERER_H
