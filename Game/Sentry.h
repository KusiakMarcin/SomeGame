#ifndef SENTRY_H
#define SENTRY_H

#include "Enemy.h"
#include "Projectile.h"

#include "ResourceManager.h"

class Sentry : public Enemy {
public:
    
   


    Sentry(int id, glm::vec2 pos, glm::vec2 size, glm::vec2 hitbox);

    void Update(float dt, Player& player) override;
     // Zwraca obiekt Projectile
    void Atack() override;
    //void Draw(SpriteRenderer& renderer, Texture2D sprite, Shader shader, glm::mat4 projection, glm::vec2 cameraPos) override;
    Projectile Shoot() override;
    // DrawGun(SpriteRenderer& renderer, Texture2D sprite, Shader shader, glm::mat4 projection, glm::vec2 cameraPos) override;
    
};

#endif