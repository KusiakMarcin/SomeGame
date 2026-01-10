#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "glm.hpp"

class GameObject
{
	
public:
	glm::vec2 Position;
	glm::vec2 Size;
	float Rotation;
	GameObject(glm::vec2 pos, glm::vec2 size, float rotation = 0.0);
	~GameObject();
	int getID();

};


#endif
