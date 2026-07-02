//
// Created by rossi on 29/06/2026.
//

#ifndef SDLPROJECT_RENDERER_H
#define SDLPROJECT_RENDERER_H


#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include "../Component/Component.h"
#include "../Actor/Actor.h"

class Renderer : public Component {
public:
    SDL_Color color = {255, 255, 255, 255};
    SDL_Texture* sprite = nullptr;

    int orderInLayer = 0;

    void Draw(SDL_Renderer* renderer) override {
        auto bounds = owner->transform.GetBounds(owner->GetWorldPosition());

        if(sprite != nullptr){

            SetTextureAlphaMod(sprite, color.a);
            SetTextureColorMod(sprite, color);
            SetRendererTexture(renderer, sprite, nullptr, &bounds);
        }else{
            SetRenderDrawColor(renderer, color);
            SetRenderFillRect(renderer, &bounds);
        }
    }

    static bool SetRenderDrawColor(SDL_Renderer* renderer, const SDL_Color color){
        return SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    }

    static bool SetRenderDrawColor(SDL_Renderer* renderer, const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a){
        return SDL_SetRenderDrawColor(renderer, r, g, b, a);
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
