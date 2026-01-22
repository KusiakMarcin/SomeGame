#include "Enemy.h"




Enemy::Enemy(int id, glm::vec2 pos, glm::vec2 size, glm::vec2 hitbox)
	: Inteligent(id, pos, size, hitbox), currentFrame(0),Color(glm::vec3(1.0f,1.0f,1.0f))
{
    FrameRate = 1.0f / 8.0f;
    WasHit = 0.0f;

    
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

void Enemy::DrawAnimation(SpriteRenderer& renderer, Texture2D sprite,
    Shader shader, glm::mat4 projection, glm::vec2 cameraPos)
{
    sprite.Wrap_S = GL_CLAMP_TO_EDGE;
    sprite.Wrap_T = GL_CLAMP_TO_EDGE;
    renderer.DrawSpriteAnimation(projection, cameraPos, sprite, shader,
        Position + glm::vec2(350.0f, 250.0f),
        currentFrame,
        FrameCount, 0.5f,
        IsFacingLeft ? MIRRORED_X : NO_MIRROR,
        Size, this->Enemy::Rotation, this->Enemy::Color);

}

void Enemy::Hit()
{
    this->HP--;
    WasHit = 0.5f;

}