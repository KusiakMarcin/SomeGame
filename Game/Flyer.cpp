#include "Flyer.h"
#include <cmath> // Dla funkcji sin()

Flyer::Flyer(int id, glm::vec2 pos, glm::vec2 size, glm::vec2 hitbox)
    : Enemy(id, pos, size, hitbox)
{
    this->MoveSpeed = 80.0f;
    this->Velocity.x = MoveSpeed;
    this->Velocity.y = 0.0f;
    this->Gravity = 0.0f;      
    this->HP = 1;              
    this->FrameCount = 4;
    this->FrameWidth = 0.25;
    Updated = false;
    this->IsKilled = false;
    ClassEnemy = "Flyer";
    this->HoverSpeed = 2.0f;   
    this->HoverAmount = 0.5f;  
    this->InitialY = pos.y;
    Aggro = glm::vec2(400.0f, 400.0f);
}

void Flyer::Update(float dt, Player& player)
{
    
    if (HP < 1) IsKilled = true;

    
    this->Position.x += this->Velocity.x * dt;

    if (!IsCreeping)
        this->Position.y += this->Velocity.y * dt;

    
    FrameRate -= dt;
    if (FrameRate <= 0)
    {
        this->currentFrame++;
        FrameRate = 1.0f / 8.0f;
    }

    if (this->currentFrame >= FrameCount) this->currentFrame = 0;

    
    if (this->Velocity.x < 0.0f) this->IsFacingLeft = false;
    if (this->Velocity.x > 0.0f) this->IsFacingLeft = true;

    
    if (WasHit > 0)
    {
        WasHit -= dt;
        Color = glm::vec3(1.0f, 0.6f, 0.6f);
    }
    else Color = glm::vec3(1.0f, 1.0f, 1.0f);

    this->UpdateAggro(); // Aktualizuje AggroCenter na œrodek Sentry
    if (!Updated) UpdatePatterns(GameObject());
    glm::vec2 playerCenter = player.Position + player.Size / 2.0f;
    glm::vec2 toPlayer = playerCenter - this->Position-this->Size;
    float distance = glm::length(toPlayer);

    // Sprawdzanie czy gracz jest w zasiêgu Aggro
    if (std::abs(toPlayer.x) < Aggro.x && std::abs(toPlayer.y) < Aggro.y) {
        PlayerDetected = true;
        
        Updated = false;
        FireAngle = std::atan2(toPlayer.y, toPlayer.x);
        
    }
    else {
        PlayerDetected = false;
        IsCreeping = true;
    }
}

void Flyer::UpdateAggro() 
{
    
    AggroCenter = this->Position + this->Size / 2.0f;
    std::cout << "FlyerAgro" << AggroCenter.x << "," << AggroCenter.y << std::endl;
    
}

void Flyer::Atack()
{
    IsCreeping = false;
    this->Velocity = glm::vec2(MoveSpeed *2* glm::cos(glm::degrees(FireAngle)), MoveSpeed *2* glm::sin(glm::degrees(FireAngle)));

}


void Flyer::UpdatePatterns(GameObject Object)
{
    if (Updated) {
        UpdateCreepingPattern(Object);


        Updated = true;
    }


}

void Flyer::UpdateCreepingPattern(GameObject ground)

{

    
    CreepingRange = glm::vec2(Position.x-200.0, Position.x+200.0);
   




}
