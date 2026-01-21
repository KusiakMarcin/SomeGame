#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "SpriteRenderer.h"
#include "Player.h"
#include "Terrain.h"
#include "Menu.h"


// Definicja stanów gry (Menu, Gra, Wygrana itp.)
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_EXIT,
    GAME_WIN
};

class Game
{
public:
    GameState State;
    bool Keys[1024]; // Tablica przechowuj¹ca stan klawiszy (Wciœniêty/Nie)
    bool LeftMouseButton;
    unsigned int Width, Height;
    glm::vec2 MousePosition;
    SpriteRenderer *Renderer;
    glm::mat4 projection;
    glm::vec2 CameraPosition;
    std::vector<Terrain> TerrainObjectsList;
    std::vector<Projectile> ProjectileObjectList;
    std::vector<Unit> UnitObjectList;
    float FrameRate;
    
    Menu MainMenu;
    TextRenderer* Text;

    static unsigned int UnitsIDs;
    


    Game(unsigned int width, unsigned int height);
    ~Game();

    // Inicjalizacja (³adowanie shaderów, tekstur, poziomów)
    void Init();

    // Pêtla Input (sterowanie)
    void ProcessInput(float dt);

    // Pêtla Logiki (aktualizacja pozycji, fizyka)
    void Update(float dt,double mousePositionX, double mousePositionY);

    // Pêtla Renderowania (rysowanie)
    void Render(float frame);

    

    void LoadLevel(const char* file);

private:

    void CheckPlayerTerrainColisions();
    void CheckProjectileColisions();
};

#endif