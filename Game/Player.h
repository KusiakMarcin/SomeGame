#ifndef PLAYER_H
#define PLAYER_H

#include <glad/glad.h>
#include <glm.hpp>

#include "Unit.h"
#include "Projectile.h"
#include <iostream>
#include <vector>


// Enum okreœlaj¹cy mo¿liwe kierunki ruchu poziomego
enum PlayerDirection {
    LEFT,
    RIGHT,
    NONE 
};

enum Weapon { RIFLE, SMG, SHOTGUN };

class Player : public Unit
{
public:
    
    
    
    glm::vec3 Color;
    glm::vec2 CrossHairPosition;
    glm::vec2 CrossHairSize;

    Weapon EquipedWeapon;
 

    int ID;
    bool IsMoving;
    bool IsFacingLeft;
    float FireRate;
    float IsFiring;
    float Gravity;      
    float JumpForce;    
    float MoveSpeed;   
    float FrameRate;
    float FireAngle;
    unsigned int currentFrame;
    unsigned int FrameCount;
    
    Texture2D Sprite;

    glm::vec2 getPosition();
    // Konstruktor
    Player(glm::vec2 pos, glm::vec2 size,Texture2D sprite,
        glm::vec3 color = glm::vec3(1.0f),
        float rotation = 0.0);

    // Metoda rysuj¹ca gracza
    void DrawAnimation(SpriteRenderer& renderer,Texture2D sprite, 
        Shader shader,glm::mat4 projection);


    void DrawIdle(SpriteRenderer& renderer, Texture2D sprite,
        Shader shader, glm::mat4 projection);

    void DrawGun(SpriteRenderer& renderer, Texture2D sprite,
        Shader shader, glm::mat4 projection);

    void DrawCrossHair(SpriteRenderer& renderer, Texture2D sprite,
        Shader shader, glm::mat4 projection);


    // Przetwarzanie wejœcia (Ustawia prêdkoœæ X i inicjuje skok)
    void ProcessKeyboard(PlayerDirection direction, float dt);

    // Metoda do skoku (wywo³ywana np. spacj¹)
    void Jump();

    Projectile Shoot();

    // G³ówna pêtla fizyki gracza (Aplikuje grawitacjê i przesuwa postaæ)
    // window_height - potrzebne do wyznaczenia "pod³ogi"
    void Update(float dt);

    // Resetowanie pozycji gracza
    void Reset(glm::vec2 position, glm::vec2 velocity);
};

#endif