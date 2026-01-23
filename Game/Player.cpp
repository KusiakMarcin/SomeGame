#include "Player.h"

glm::vec2 playerCenter(350.0f, 250.0f);

Player::Player(glm::vec2 pos, glm::vec2 size, Texture2D sprite,
    glm::vec3 color, float rotation)
    : Unit(1,pos, size,glm::vec2(3.0f,0.0f), rotation), Sprite(sprite), Color(color), FrameRate(1.0f / 8.0f),
    FrameCount(3), currentFrame(0), IsFiring(false),ID(1),
    CrossHairSize(glm::vec2(30.0f,30.0f)),EquipedWeapon(RIFLE), FireRate(1.0f)
{
 
    this->MoveSpeed = 300.0f;   
    this->Gravity = 1600.0f;    
    this->JumpForce = 1000.0f;   
    this->IsGrounded = false;
    IsKilled = false;
    HP = 3;
    
    
}

void Player::DrawAnimation(SpriteRenderer& renderer,Texture2D sprite, Shader shader, glm::mat4 projection)
{
    sprite.Wrap_S = GL_CLAMP_TO_EDGE;
    sprite.Wrap_T = GL_CLAMP_TO_EDGE;
    
    renderer.DrawSpriteAnimation(projection,-this->Position, sprite, shader,
        this->Position + playerCenter,
        this->currentFrame,
        this->FrameCount,0.25f, 
        this->IsFacingLeft ? MIRRORED_X : NO_MIRROR,
        this->Size, this->Rotation, this->Color);
}


void Player::DrawIdle(SpriteRenderer& renderer, Texture2D sprite, Shader shader, glm::mat4 projection)
{
    sprite.Wrap_S = GL_CLAMP_TO_EDGE;
    sprite.Wrap_T = GL_CLAMP_TO_EDGE;

    renderer.DrawSprite(projection, -this->Position, sprite, shader,
        this->Position + playerCenter,
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
      renderer.DrawSprite(projection, -this->Position , sprite, shader,
          GunPosition + playerCenter,NO_MIRROR, glm::vec2(60.0f,20.0f),
        glm::degrees(FireAngle), this->Color);
    else
        renderer.DrawSprite(projection, -this->Position , sprite, shader,
            GunPosition + playerCenter, MIRRORED_Y, glm::vec2(60.0f, 20.0f),
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
    else 
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
    
    if (HP < 1) IsKilled = true;

    if (this->Velocity.x == 0.0f && this->Velocity.y == 0.0f) this->IsMoving = false;
    else this->IsMoving = true;


    if (this->Velocity.y > 0.0f) this->IsGrounded = false;



    this->Velocity.y += this->Gravity * dt;
    this->FrameRate -= dt;
    if (this->FrameRate <= 0)
    {
        this->currentFrame++;
        this->FrameRate = 1.0f / 8.0f;
    }

    if (IsFiring > 0.0f) this->IsFiring -= dt;
    else this->IsFiring = 0.0f;


    if (WasHit > 0.0)
    {

        WasHit -= dt;
        Color = glm::vec3(1.0f, 0.0f, 0.0f);
    }
    else Color = glm::vec3(1.0f, 1.0f, 1.0f);

    if (IsVunerable > 0.0&&WasHit<=0.0f)
    {

        IsVunerable -= dt;
        Color = glm::vec3(1.2f, 1.2f, 1.2f);
    }
    else Color = glm::vec3(1.0f, 1.0f, 1.0f);
   
    
    
    glm::vec2 tmp(CrossHairPosition.x - playerCenter.x,CrossHairPosition.y - playerCenter.y);
    
    FireAngle = glm::atan(tmp.y, tmp.x);
    
    // 2. Przesuniêcie gracza na podstawie prêdkoœci
    this->Position.x += this->Velocity.x * dt;
    this->Position.y += this->Velocity.y * dt;


    if (std::abs(this->Velocity.x) > 1500.0f)  this->Velocity.x = 1500.0f;
    if (std::abs(this->Velocity.y) > 1500.0f)  this->Velocity.y = 1500.0f;
    
    

    
    
    
}

void Player::Hit()
{

    this->Velocity.y = -500.0f;
    this->HP--;
    WasHit = 0.5f;
    this->IsVunerable = 1.5f;


}

Projectile Player::Shoot()
{
   
    switch (this->EquipedWeapon) {
     
    case RIFLE:
        //std::cout << "Rifle" << std::endl;
        float velocityX = 1000.0f * glm::cos(FireAngle);
        float velocityY = 1000.0f * glm::sin(FireAngle);

        //std::cout << velocityX << "," << velocityY << std::endl;
        Projectile newProjectile (this->ID, this->Position +glm::vec2(10.0f,30.0f),
            glm::vec2(20.0f, 10.0f),
            glm::vec2(velocityX, velocityY),
            1000.0f, glm::degrees(FireAngle));
        this->IsFiring = 1.0f;
        return newProjectile;
        break;
    }


}

void Player::Reset(glm::vec2 position, glm::vec2 velocity)
{
    this->Position = position;
    this->Velocity = velocity;
    this->Rotation = 0.0f;
    this->IsGrounded = false;
}

