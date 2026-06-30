//
// Created by rossi on 29/06/2026.
//

#ifndef SDLPROJECT_GAME_H
#define SDLPROJECT_GAME_H

#include <SDL3/SDL.h>
#include <vector>
#include "../../Actor/Actor.h"

class Game {
public:
    Game();
    ~Game();

    void Run();
    Actor* CreateActor();

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

private:
    void Init();
    void ProcessEvents();
    void Update(float deltaTime);
    void Render();
    void Shutdown();

    SDL_Window* m_Window = nullptr;
    SDL_Renderer* m_Renderer = nullptr;

    bool m_LayerOrderDirty = true;
    bool m_IsRunning = false;

    std::vector<Actor*> m_Actors;
};

#endif //SDLPROJECT_GAME_H
