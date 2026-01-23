#include "Sentry.h"
#include <cmath>


Sentry::Sentry(int id, glm::vec2 pos, glm::vec2 size, glm::vec2 hitbox)
    : Enemy(id, pos, size, hitbox)
    
{
    Color = glm::vec3(1.0f, 1.0f, 1.0f);
    FireCooldown = 1.0f;
    
    PlayerDetected = false;
    this->Gravity = 0.0f;
    this->Velocity = glm::vec2(0.0f);
    this->Aggro = glm::vec2(500.0f, 500.0f); // Zasiêg wzroku wie¿yczki
    ClassEnemy = "Sentry";
    FireAngle = 0.0f;
    FrameWidth = 1.0f;
    FrameCount = 1;
    this ->HP = 4;
    
    
}

void Sentry::Atack()
{

    ;
}

void Sentry::Update(float dt, Player& player) 
{
    this->UpdateAggro(); // Aktualizuje AggroCenter na œrodek Sentry

    glm::vec2 playerCenter = player.Position + player.Size / 2.0f;
    glm::vec2 toPlayer = playerCenter - this->AggroCenter;
    float distance = glm::length(toPlayer);

    if (WasHit > 0)
    {

        WasHit -= dt;
        Color = glm::vec3(1.0f, 0.6f, 0.6f);
    }
    else Color = glm::vec3(1.0f, 1.0f, 1.0f);

    // Sprawdzanie czy gracz jest w zasiêgu Aggro
    if (std::abs(toPlayer.x) < Aggro.x && std::abs(toPlayer.y) < Aggro.y) {
        PlayerDetected = true;
        // Obliczamy k¹t lufy (w radianach)
        FireAngle = std::atan2(toPlayer.y, toPlayer.x);

        
    }
    else {
        PlayerDetected = false;
    }
    if (FireCooldown > 0) FireCooldown -= dt;
    // Logika WasHit i HP z klasy Enemy
    if (this->HP < 1) this->IsKilled = true;
    if (this->WasHit > 0) this->WasHit -= dt;
}

Projectile Sentry::Shoot() {
     this->FireCooldown = 1.0f;

    // Kierunek na podstawie k¹ta
    glm::vec2 direction = glm::vec2(std::cos(FireAngle), std::sin(FireAngle));
    glm::vec2 projVelocity = direction * 500.0f; // Prêdkoœæ pocisku
    glm::vec2 projSize = glm::vec2(20.0f, 10.0f);

    // Zasiêg pocisku (FireRange)
    float range = 800.0f;

    // Zgodnie z Twoim konstruktorem: (sourceID, pos, size, velocity, fireRange, rotation)
    return Projectile(this->ID, this->AggroCenter - (projSize / 2.0f)-glm::vec2(0.0f,16.0f), projSize, projVelocity, range, glm::degrees(FireAngle));
}

