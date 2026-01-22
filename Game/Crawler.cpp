#include "Crawler.h"
#include <iostream>

Crawler::Crawler(int id, glm::vec2 pos, glm::vec2 size, glm::vec2 hitbox)
    : Enemy(id,pos,size,hitbox)
{

    MoveSpeed = 100.0f;
    this->Velocity.x = MoveSpeed;
    this->HP = 2;
    FrameCount = 2;
    IsKilled = false;

}

void Enemy::Update(float dt) 
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
    if ((CreepingRange.x > Position.x) || (Position.x > CreepingRange.y-Size.x))
        
        Velocity.x = -Velocity.x;
    UpdateAggro();
   
    
    //std::cout << this->HP << std::endl;

   

  
    this->Position.x += this->Velocity.x * dt;
    this->Position.y += this->Velocity.y * dt;




}


void Inteligent::UpdateAggro()
{
    
	AggroCenter = this->Position + this->Size / 2.0f;
	

}


void Inteligent::UpdatePatterns(GameObject Object)
{

    UpdateCreepingPattern(Object);
    
   
    



}

void Inteligent::UpdateCreepingPattern(GameObject ground)

{
    
    if (this->IsGrounded)
    {
        CreepingRange = glm::vec2(ground.Position.x, ground.Position.x + ground.Size.x);
    }
    
    


}

