//
// Created by rossi on 30/06/2026.
//

#include "InputManager.h"

void InputManager::NewFrame() {
    m_KeysPressed.clear();
    m_KeysReleased.clear();

    m_MouseButtonsPressed.clear();
    m_MouseButtonsReleased.clear();
}

void InputManager::ProcessEvent(const SDL_Event &event) {
    switch (event.type) {
        case SDL_EVENT_KEY_DOWN:
            if(!event.key.repeat){
                m_KeysDown.insert(event.key.scancode);
            }
            break;

        case SDL_EVENT_KEY_UP:
            m_KeysDown.erase(event.key.scancode);
            m_KeysReleased.insert(event.key.scancode);
            break;

        case SDL_EVENT_MOUSE_MOTION:
            m_MousePosition = { event.motion.x, event.motion.y };
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            m_MouseButtonsDown.insert(event.button.button);
            m_MouseButtonsPressed.insert(event.button.button);
            break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
            m_MouseButtonsDown.erase(event.button.button);
            m_MouseButtonsReleased.insert(event.button.button);
            break;

        default:
            break;
    }
}

bool InputManager::IsKeyDown(SDL_Scancode key) const {
    return m_KeysDown.contains(key);
}

bool InputManager::IsKeyPressed(SDL_Scancode key) const {
    return m_KeysPressed.contains(key);
}

bool InputManager::IsKeyReleased(SDL_Scancode key) const {
    return m_KeysReleased.contains(key);
}

bool InputManager::IsMouseButtonDown(Uint8 button) const {
    return m_MouseButtonsDown.contains(button);
}

bool InputManager::IsMouseButtonPressed(Uint8 button) const {
    return m_MouseButtonsPressed.contains(button);
}

bool InputManager::IsMouseButtonReleased(Uint8 button) const {
    return m_MouseButtonsReleased.contains(button);
}
