#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Klasa zarz¹dzaj¹ca stanem wejœcia (Klawiatura/Mysz)
class InputManager {
public:
    // Tablica przechowuj¹ca stan wszystkich klawiszy (true = wciœniêty)
    static bool Keys[1024];
    // Tablica pomocnicza do wykrywania "jednorazowego" wciœniêcia (zapobiega ci¹g³emu triggeringowi)
    static bool KeysProcessed[1024];

    // Metoda czyszcz¹ca stan (resetuje flagi processed) - wywo³ywana co klatkê? 
    // W tym przypadku raczej resetujemy konkretne stany, tu zostawiam jako interfejs.
    static void Init();

    // Sprawdza, czy klawisz jest wciœniêty (zwraca true w ka¿dej klatce trzymania)
    static bool IsKeyHeld(int key);

    // Sprawdza, czy klawisz zosta³ wciœniêty w tej klatce (zwraca true tylko raz)
    static bool IsKeyPressed(int key);
};

#endif