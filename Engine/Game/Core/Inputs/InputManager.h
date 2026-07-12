//
// Created by rossi on 30/06/2026.
//

#ifndef SDLPROJECT_INPUTMANAGER_H
#define SDLPROJECT_INPUTMANAGER_H


#include <SDL3/SDL_events.h>
#include "../Math/Vector2.h"
#include <unordered_set>

class InputManager {
public:
    static InputManager& Instance(){
        static InputManager instance;
        return instance;
    }

    void NewFrame();
    void ProcessEvent(const SDL_Event& event);

    bool IsKeyDown(SDL_Scancode key) const;
    bool IsKeyPressed(SDL_Scancode key) const;
    bool IsKeyReleased(SDL_Scancode key) const;

    Vector2 GetMousePosition() const { return m_MousePosition; };
    bool IsMouseButtonDown(Uint8 button) const;
    bool IsMouseButtonPressed(Uint8 button) const;
    bool IsMouseButtonReleased(Uint8 button) const;

    float GetAxis(SDL_Scancode negativeKey, SDL_Scancode positiveKey);
    Vector2 GetAxis2D(SDL_Scancode leftKey, SDL_Scancode rightKey, SDL_Scancode upKey, SDL_Scancode downKey);

private:
    InputManager() = default;

    std::unordered_set<SDL_Scancode> m_KeysDown;
    std::unordered_set<SDL_Scancode> m_KeysPressed;
    std::unordered_set<SDL_Scancode> m_KeysReleased;

    Vector2 m_MousePosition;
    std::unordered_set<Uint8> m_MouseButtonsDown;
    std::unordered_set<Uint8> m_MouseButtonsPressed;
    std::unordered_set<Uint8> m_MouseButtonsReleased;
};


#endif //SDLPROJECT_INPUTMANAGER_H
