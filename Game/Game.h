#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "SpriteRenderer.h"
#include "Terrain.h"
#include <vector>

// Definicja stanów gry (Menu, Gra, Wygrana itp.)
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game
{
public:
    GameState    State;
    bool         Keys[1024]; // Tablica przechowuj¹ca stan klawiszy (Wciœniêty/Nie)
    unsigned int Width, Height;
    SpriteRenderer *Renderer;
    glm::mat4 projection;
    std::vector<Terrain> TerrainObjectsList;
    float FrameRate;
    


    Game(unsigned int width, unsigned int height);
    ~Game();

    // Inicjalizacja (³adowanie shaderów, tekstur, poziomów)
    void Init();

    // Pêtla Input (sterowanie)
    void ProcessInput(float dt);

    // Pêtla Logiki (aktualizacja pozycji, fizyka)
    void Update(float dt);

    // Pêtla Renderowania (rysowanie)
    void Render();
};

#endif