//
// Created by rossi on 29/06/2026.
//
#include "Actor.h"
#include "../Game/Game.h"


void Actor::Draw(SDL_Renderer* sdlRenderer) const {
    auto bounds = transform.GetBounds(GetWorldPosition());

    if(renderer.sprite != nullptr){
        SDL_SetTextureColorMod(
                renderer.sprite,
                renderer.color.r,
                renderer.color.g,
                renderer.color.b
                );
        SDL_SetTextureAlphaMod(renderer.sprite, renderer.color.a);
        SDL_RenderTexture(sdlRenderer, renderer.sprite, nullptr, &bounds);
    }
    else{
        Game::SetRenderDrawColor(sdlRenderer, renderer.color);
        Game::SetRenderFillRect(sdlRenderer, &bounds);
    }
}

void Actor::Update(float deltaTime) {

}
