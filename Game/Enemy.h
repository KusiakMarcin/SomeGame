#ifndef ENEMY_H
#define ENEMY_H




#include "Inteligent.h"
#include "Player.h"



class Enemy : public Inteligent
{
public:
	
	unsigned int currentFrame;
	unsigned int FrameCount;
	float FrameRate;
	float FrameWidth;
	std::string ClassEnemy;
	float FireAngle;
	glm::vec3 Color;
	float FireCooldown;
	
	Texture2D GunSprite;
	bool PlayerDetected;
	
	Enemy();
	Enemy(int id, glm::vec2 pos, glm::vec2 size, glm::vec2 hitbox);
	
	void Death();
	
	void Draw(SpriteRenderer& renderer, Texture2D sprite, Shader shader, glm::mat4 projection, glm::vec2 cameraPos);

	void DrawGun(SpriteRenderer& renderer, Texture2D sprite, Shader shader, glm::mat4 projection, glm::vec2 cameraPos);
    void DrawAnimation(SpriteRenderer& renderer, Texture2D sprite,
		Shader shader, glm::mat4 projection, glm::vec2 cameraPos);
	
	virtual void Update(float dt, Player& player);
	virtual Projectile Shoot();
	
	virtual void Atack();
	void Hit();
	

	
	

};

#endif 