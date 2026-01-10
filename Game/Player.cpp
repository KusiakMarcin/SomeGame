#include "Player.h"


Player::Player(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec2 velocity,
    glm::vec3 color,float rotation)
    : GameObject(pos, size,rotation), Sprite(sprite), Color(color),Velocity(velocity)
{
    // Konfiguracja fizyki platformowej
    this->MoveSpeed = 300.0f;   // Prêdkoœæ biegania
    this->Gravity = 1500.0f;    // Si³a grawitacji (musi byæ du¿a w pikselach)
    this->JumpForce = 1000.0f;   // Si³a wybicia w górê
    this->IsGrounded = false;
    
}

void Player::Draw(SpriteRenderer& renderer,Texture2D sprite, Shader shader, glm::mat4 projection)
{
    renderer.DrawSprite(projection,sprite,shader, this->Position, this->Size, this->Rotation, this->Color);
}

void Player::ProcessKeyboard(PlayerDirection direction, float dt)
{
    // W platformówce klawisze lewo/prawo ustawiaj¹ prêdkoœæ X
    if (direction == LEFT)
    {
        this->Velocity.x = -this->MoveSpeed;
    }
    else if (direction == RIGHT)
    {
        this->Velocity.x = this->MoveSpeed;
    }
    else // NONE
    {
        this->Velocity.x = 0.0f;
    }
}

void Player::Jump()
{
    // Mo¿emy skoczyæ tylko, jeœli stoimy na ziemi
    if (this->IsGrounded)
    {
        this->Velocity.y = -this->JumpForce; // Minus, bo Y=0 jest na górze ekranu
        this->IsGrounded = false; // Jesteœmy w powietrzu
    }
}

void Player::Update(float dt, float window_height)
{
    // 1. Aplikacja grawitacji do prêdkoœci Y
    // Zwiêkszamy prêdkoœæ w dó³ w ka¿dej klatce (symulacja przyspieszenia ziemskiego)
    
    this->Velocity.y += this->Gravity * dt;

    // 2. Przesuniêcie gracza na podstawie prêdkoœci
    this->Position.x += this->Velocity.x * dt;
    this->Position.y += this->Velocity.y * dt;

    // 3. Detekcja kolizji z "Pod³og¹" (Dó³ ekranu)
    float groundLevel = window_height - this->Size.y;

    if (this->Position.y >= groundLevel)
    {
        this->Position.y = groundLevel; // Przyklej do ziemi (korekcja pozycji)
        this->Velocity.y = 0.0f;        // Zatrzymaj spadanie
        this->IsGrounded = true;        // Flaguj, ¿e mo¿na skoczyæ
    }
    else
    {
        // Jeœli jesteœmy nad ziemi¹, to znaczy, ¿e spadamy lub skaczemy
        this->IsGrounded = false;
    }

    

    if (this->Velocity.x == 0.0f && this->Velocity.y == 0.0f) this->IsMoving = false;
    else this->IsMoving = true;
    // Tutaj mo¿na dodaæ ograniczenie z prawej strony, jeœli znasz szerokoœæ okna
    // else if (this->Position.x + this->Size.x > window_width) { ... }
}

void Player::Reset(glm::vec2 position, glm::vec2 velocity)
{
    this->Position = position;
    this->Velocity = velocity;
    this->Rotation = 0.0f;
    this->IsGrounded = false;
}