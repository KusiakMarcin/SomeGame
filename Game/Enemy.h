#ifndef ENEMY_H
#define ENEMY_H




#include "Inteligent.h"


class Enemy : public Inteligent
{
public:
	
	unsigned int currentFrame;
	unsigned int FrameCount;
	float FrameRate;
	
	glm::vec3 Color;
	
	
	Enemy();
	Enemy(int id, glm::vec2 pos, glm::vec2 size, glm::vec2 hitbox);
	

     void DrawAnimation(SpriteRenderer& renderer, Texture2D sprite,
		Shader shader, glm::mat4 projection, glm::vec2 cameraPos);

	virtual void Update(float dt);
	void Death();
	/*virtual void Atack();*/
	void Hit();
	

	
	

};

#endif 