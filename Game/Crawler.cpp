#include "Crawler.h"
#include <iostream>

Crawler::Crawler(int id, glm::vec2 pos, glm::vec2 size, glm::vec2 hitbox)
    : Enemy(id,pos,size,hitbox)
{

    MoveSpeed = 100.0f;
    this->Velocity.x = MoveSpeed;
    this->HP = 2;
    FrameCount = 2;
    FrameWidth = 0.5;
    Updated = false;
    IsKilled = false;
    ClassEnemy = "Crawler";
    Aggro = glm::vec2(150.0f, this->Size.y);

}

void Crawler::Update(float dt, Player& player)
{

    if (HP < 1) IsKilled = true;
    
    
    
    
    if (this->Velocity.x == 0.0f && this->Velocity.y == 0.0f) this->IsMoving = false;
    else this->IsMoving = true;


    if (this->Velocity.y > 0.0f) this->IsGrounded = false;

    if (this->Velocity.x < 0.0f) this->IsFacingLeft = false;
    if (this->Velocity.x > 0.0f) this->IsFacingLeft = true;

    this->Velocity.y += this->Gravity * dt;
    

    //std::cout << WasHit << std::endl;
    
    if (WasHit > 0)
    {

        WasHit -= dt;
        Color = glm::vec3(1.0f, 0.6f, 0.6f);
    }
    else Color = glm::vec3(1.0f, 1.0f, 1.0f);

    FrameRate -= dt;
    if (FrameRate <= 0)
    {
        this->currentFrame++;
        FrameRate = 1.0f / 8.0f;
    }
    
    //std::cout << "creeping:" << CreepingRange.x << "," << CreepingRange.y << std::endl;
    
    //std::cout << "Position:" << Position.x << "," <<Position.y << std::endl;
    
    if ((CreepingRange.x > Position.x) || (Position.x > CreepingRange.y - Size.x))
        Velocity.x = -Velocity.x;
    if (Velocity.x > MoveSpeed) Velocity.x = Velocity.x / 2.0;
    this->UpdateAggro(); 

    glm::vec2 playerCenter = player.Position + player.Size / 2.0f;
    glm::vec2 toPlayer = playerCenter - this->AggroCenter;
    float distance = glm::length(toPlayer);

    // Sprawdzanie czy gracz jest w zasiêgu Aggro
    if (std::abs(toPlayer.x) < Aggro.x && std::abs(toPlayer.y) < Aggro.y) {
        PlayerDetected = true;
        
     
    }
    else {
        PlayerDetected = false;
        
    }
    
    //std::cout << this->HP << std::endl;

   

  
    this->Position.x += this->Velocity.x * dt;
    this->Position.y += this->Velocity.y * dt;




}

void Crawler::Atack()
{


    ;

}

void Crawler::UpdateAggro()
{
    
	AggroCenter = this->Position + this->Size / 2.0f+(IsFacingLeft ? glm::vec2(150.0f, 0.0f) : -glm::vec2(150.0f, 0.0f));
	

}


void Crawler::UpdatePatterns(GameObject Object)
{
    
    
        UpdateCreepingPattern(Object);
        Updated = true;
    
    



}

void Crawler::UpdateCreepingPattern(GameObject ground)

{
    
    if (this->IsGrounded)
    {
        CreepingRange = glm::vec2(ground.Position.x, ground.Position.x + ground.Size.x);
        
    }
    
    


}

