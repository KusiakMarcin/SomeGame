#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "GameObject.h"

class Projectile : public GameObject
{

private:

	void UpdateRotation();


public:
	
	
	int SourceID;
	float Radius;
	float AxisXShift;
	glm::vec3 Color;
	glm::vec2 Velocity;
	double FireRange;
	
	Projectile();
	Projectile(int sourceID,glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, float fireRange, float rotation = 0.0);
	
	void Update(float dt);
	
	void Draw(SpriteRenderer& renderer, Texture2D sprite, Shader shader, glm::mat4 projection, glm::vec2 cameraPos);

	
};

#endif 


