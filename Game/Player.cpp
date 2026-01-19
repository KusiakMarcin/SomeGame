#include "Player.h"

glm::vec2 playerCenter(350.0f, 250.0f);

Player::Player(glm::vec2 pos, glm::vec2 size, Texture2D sprite,
    glm::vec3 color, float rotation)
    : GameObject(pos, size, rotation), Sprite(sprite), Color(color), FrameRate(1.0f/8.0f),
    FrameCount(3), currentFrame(0), IsFiring(false),CrossHairSize(glm::vec2(30.0f,30.0f)),IsFacingLeft(false)
{
    // Konfiguracja fizyki platformowej
    this->MoveSpeed = 300.0f;   // Prêdkoœæ biegania
    this->Gravity = 1600.0f;    // Si³a grawitacji (musi byæ du¿a w pikselach)
    this->JumpForce = 1000.0f;   // Si³a wybicia w górê
    this->IsGrounded = false;
    
}

void Player::DrawAnimation(SpriteRenderer& renderer,Texture2D sprite, Shader shader, glm::mat4 projection)
{
    sprite.Wrap_S = GL_CLAMP_TO_EDGE;
    sprite.Wrap_T = GL_CLAMP_TO_EDGE;
    renderer.DrawSpriteAnimation(projection,-this->Position+playerCenter, sprite, shader,
        this->Position,
        this->currentFrame,
        this->FrameCount,0.25f, 
        this->IsFacingLeft ? MIRRORED_X : NO_MIRROR,
        this->Size, this->Rotation, this->Color);
}


void Player::DrawIdle(SpriteRenderer& renderer, Texture2D sprite, Shader shader, glm::mat4 projection)
{
    sprite.Wrap_S = GL_CLAMP_TO_EDGE;
    sprite.Wrap_T = GL_CLAMP_TO_EDGE;

    renderer.DrawSprite(projection, -this->Position+playerCenter, sprite, shader,
        this->Position,
        this->IsFacingLeft ? MIRRORED_X : NO_MIRROR,
        this->Size,
        this->Rotation,
        this->Color);

}

void Player::DrawGun(SpriteRenderer& renderer, Texture2D sprite, Shader shader, glm::mat4 projection)
{
    sprite.Wrap_S = GL_CLAMP_TO_EDGE;
    sprite.Wrap_T = GL_CLAMP_TO_EDGE;
    glm::vec2 GunPosition = glm::vec2(-10.0f, 30.0f);
    GunPosition += this->Position;
    
     
    if (this->CrossHairPosition.x > 400.0f) 
      renderer.DrawSprite(projection, -this->Position + playerCenter, sprite, shader,
          GunPosition,NO_MIRROR, glm::vec2(60.0f,20.0f),
        glm::degrees(FireAngle), this->Color);
    else
        renderer.DrawSprite(projection, -this->Position + playerCenter, sprite, shader,
            GunPosition, MIRRORED_Y, glm::vec2(60.0f, 20.0f),
            glm::degrees(FireAngle), this->Color);
}

void Player::DrawCrossHair(SpriteRenderer& renderer, Texture2D sprite,
    Shader shader, glm::mat4 projection)
{
    glm::vec2 shift = glm::vec2(20.0f, 20.0f);
    renderer.DrawSprite(projection, glm::vec2(0.0f, 0.0f), sprite, shader,
        this->CrossHairPosition + shift,false,
        this->CrossHairSize, this->Rotation, this->Color);

}

void Player::ProcessKeyboard(PlayerDirection direction, float dt)
{
    // W platformówce klawisze lewo/prawo ustawiaj¹ prêdkoœæ X
    if (direction == LEFT)
    {
        this->Velocity.x = -this->MoveSpeed;
        IsFacingLeft = true;
    }
    else if (direction == RIGHT)
    {
        this->Velocity.x = this->MoveSpeed;
        IsFacingLeft = false;
    }
    else // NONE
    {
        this->Velocity.x = 0.0f;
    }
}

void Player::Jump()
{
    
    if (this->IsGrounded)
    {
        this->Velocity.y = -this->JumpForce; 
        this->IsGrounded = false; 
    }
}



void Player::Update(float dt)
{
    // 1. Aplikacja grawitacji do prêdkoœci Y
    // Zwiêkszamy prêdkoœæ w dó³ w ka¿dej klatce (symulacja przyspieszenia ziemskiego)
    std::cout << "velocity:" << this->Velocity.x << "," << this->Velocity.y << std::endl;
    if (this->Velocity.x == 0.0f && this->Velocity.y == 0.0f) this->IsMoving = false;
    else this->IsMoving = true;



    this->Velocity.y += this->Gravity * dt;
    this->FrameRate -= dt;
    if (this->FrameRate <= 0)
    {
        this->currentFrame++;
        this->FrameRate = 1.0f / 8.0f;
    }

    
   
    
    
    glm::vec2 tmp(CrossHairPosition.x - playerCenter.x,CrossHairPosition.y - playerCenter.y);
    std::cout << "tmpx:" << tmp.x << "tmpy" << tmp.x << std::endl;
    FireAngle = glm::atan(tmp.y, tmp.x);
    
    // 2. Przesuniêcie gracza na podstawie prêdkoœci
    this->Position.x += this->Velocity.x * dt;
    this->Position.y += this->Velocity.y * dt;


    if (this->Velocity.x > 1500.0f)  this->Velocity.x = 1500.0f;
    if (this->Velocity.y > 1500.0f)  this->Velocity.y = 1500.0f;
   
    

    
    
    
}

void Player::Reset(glm::vec2 position, glm::vec2 velocity)
{
    this->Position = position;
    this->Velocity = velocity;
    this->Rotation = 0.0f;
    this->IsGrounded = false;
}