#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "glm.hpp"

class GameObject
{
	
public:
	glm::vec2 Position;
	glm::vec2 Size;
	glm::vec2 Hitbox;
	glm::vec2 Velocity;
	bool IsPhisical;
	bool IsMovable;
	bool IsGrounded;
	float Rotation;
	GameObject(glm::vec2 pos, glm::vec2 size, bool isMovable, float rotation = 0.0,
		bool isPhisical = true,bool isGrounded = false);
	~GameObject();
	int getID();
	
};


#endif
