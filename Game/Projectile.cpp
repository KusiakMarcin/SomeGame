#include "Projectile.h"


Projectile::Projectile(int sourceID,glm::vec2 pos, glm::vec2 size,glm::vec2 velocity,float fireRange, float rotation)
	: GameObject(pos,size,rotation), Velocity(velocity), FireRange(fireRange),
    SourceID(sourceID), Color(glm::vec3(1.0f,1.0f,1.0f))
{

    Radius = size.y/2.0f;
    AxisXShift = size.x-(Radius/2.0f);

}

void Projectile::Draw(SpriteRenderer& renderer, Texture2D sprite, Shader shader, glm::mat4 projection, glm::vec2 cameraPos)
{
    sprite.Wrap_S = GL_CLAMP_TO_EDGE;
    sprite.Wrap_T = GL_CLAMP_TO_EDGE;

    renderer.DrawSprite(projection, cameraPos , sprite, shader,
        this->Position + glm::vec2(350.0f, 250.f),
        NO_MIRROR,
        this->Size,
        this->Rotation,
        this->Color);

}

void Projectile::Update(float dt)
{
    this->Position.x += this->Velocity.x * dt;
    this->Position.y += this->Velocity.y * dt;
    FireRange -= glm::sqrt(glm::pow(Velocity.x, 2) + glm::pow(Velocity.y, 2));
    
}