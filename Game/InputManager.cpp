#include "InputManager.h"
#include <algorithm>

// Inicjalizacja statycznych sk³adowych
bool InputManager::Keys[1024];
bool InputManager::KeysProcessed[1024];

void InputManager::Init() {
    // Zerowanie tablic
    std::fill(std::begin(Keys), std::end(Keys), false);
    std::fill(std::begin(KeysProcessed), std::end(KeysProcessed), false);
}

bool InputManager::IsKeyHeld(int key) {
    if (key >= 0 && key < 1024)
        return Keys[key];
    return false;
}

bool InputManager::IsKeyPressed(int key) {
    // Jeœli klawisz jest wciœniêty, ale jeszcze nie przetworzony
    if (key >= 0 && key < 1024) {
        if (Keys[key] && !KeysProcessed[key]) {
            KeysProcessed[key] = true;
            return true;
        }
    }
    return false;
}