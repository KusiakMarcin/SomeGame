#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "glm.hpp"
#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"

class GameObject
{
	
public:
	
	glm::vec2 Position;
	glm::vec2 Size;
	
	bool IsPhisical;
	
	
	float Rotation;
	GameObject(glm::vec2 pos, glm::vec2 size, float rotation = 0.0,
		bool isPhisical = true);
	~GameObject();
	int getID();
	
};


#endif
