#include "Enemy.h"




Enemy::Enemy(int id, glm::vec2 pos, glm::vec2 size, glm::vec2 hitbox)
	: Inteligent(id, pos, size, hitbox), currentFrame(0),Color(glm::vec3(1.0f,1.0f,1.0f))
{
    FrameRate = 1.0f / 8.0f;
    WasHit = 0.0f;
    IsKilled = false;

    
}

Enemy::Enemy()
{

    ;

}


void Enemy::Death()
{

    Color = glm::vec3(1.0f, 0.0f, 0.0f);
    IsKilled = true;

}


void Enemy::Update(float dt, Player& player)
{

    ;

}
void Enemy::Atack()
{

    ;
}

Projectile Enemy::Shoot()
{

    return Projectile();
}

void Enemy::Draw(SpriteRenderer& renderer, Texture2D sprite, Shader shader, glm::mat4 projection, glm::vec2 cameraPos) {
    sprite.Wrap_S = GL_CLAMP_TO_EDGE;
    sprite.Wrap_T = GL_CLAMP_TO_EDGE;
    renderer.DrawSprite(projection, cameraPos, sprite, shader, this->Position + glm::vec2(350.0f, 250.0f), NO_MIRROR, this->Size, 0.0f, this->Color);
}

void Enemy::DrawGun(SpriteRenderer& renderer, Texture2D sprite, Shader shader, glm::mat4 projection, glm::vec2 cameraPos) {
    glm::vec2 gunSize = glm::vec2(this->Size.x * 2.0f, this->Size.y * 0.3f);

    sprite.Wrap_S = GL_CLAMP_TO_EDGE;
    sprite.Wrap_T = GL_CLAMP_TO_EDGE;

    renderer.DrawSprite(projection, cameraPos, sprite, shader,
        this->Position - glm::vec2(20.0f, (gunSize.y / 2.0f) - 3.0f) + glm::vec2(350.0f, 250.0f),
        NO_MIRROR, gunSize, glm::degrees(FireAngle), this->Color);
}





void Enemy::DrawAnimation(SpriteRenderer& renderer, Texture2D sprite,
    Shader shader, glm::mat4 projection, glm::vec2 cameraPos)
{
    sprite.Wrap_S = GL_CLAMP_TO_EDGE;
    sprite.Wrap_T = GL_CLAMP_TO_EDGE;
    renderer.DrawSpriteAnimation(projection, cameraPos, sprite, shader,
        Position + glm::vec2(350.0f, 250.0f),
        currentFrame,
        FrameCount, FrameWidth,
        IsFacingLeft ? MIRRORED_X : NO_MIRROR,
        Size, this->Enemy::Rotation, this->Enemy::Color);

}



void Enemy::Hit()
{
    this->HP--;
    WasHit = 0.5f;

}