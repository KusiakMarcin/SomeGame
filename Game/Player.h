#ifndef PLAYER_H
#define PLAYER_H

#include <glad/glad.h>
#include <glm.hpp>

#include "GameObject.h"

#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"

// Enum okreœlaj¹cy mo¿liwe kierunki ruchu poziomego
enum PlayerDirection {
    LEFT,
    RIGHT,
    NONE // Brak ruchu poziomego
};

class Player : GameObject
{
public:
    // W³aœciwoœci publiczne gracza
    
    glm::vec2 Velocity;
    glm::vec3 Color;

    // Zmienne fizyki
    bool IsGrounded;   // Czy stoi na ziemi?
    bool IsMoving;
    float Gravity;      // Si³a przyci¹gania (piksele na sekundê^2)
    float JumpForce;    // Si³a wyskoku
    float MoveSpeed;    // Prêdkoœæ poruszania siê w poziomie

    // Tekstura gracza (Sprite)
    Texture2D Sprite;

    // Konstruktor
    Player(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec2 velocity, glm::vec3 color = glm::vec3(1.0f), float rotation = 0.0);

    // Metoda rysuj¹ca gracza
    void Draw(SpriteRenderer& renderer,Texture2D sprite, Shader shader,glm::mat4 projection);

    // Przetwarzanie wejœcia (Ustawia prêdkoœæ X i inicjuje skok)
    void ProcessKeyboard(PlayerDirection direction, float dt);

    // Metoda do skoku (wywo³ywana np. spacj¹)
    void Jump();

    // G³ówna pêtla fizyki gracza (Aplikuje grawitacjê i przesuwa postaæ)
    // window_height - potrzebne do wyznaczenia "pod³ogi"
    void Update(float dt, float window_height);

    // Resetowanie pozycji gracza
    void Reset(glm::vec2 position, glm::vec2 velocity);
};

#endif