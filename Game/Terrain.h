#pragma once
#include "GameObject.h"
#include "SpriteRenderer.h"



enum type{DIRT,WOOD,METAL};

class Terrain :public GameObject
{
public:
	
	int HP;
	std::string TerrainClass;
	bool isDestructable;
	bool isMovable;
	bool isHarmful;
	glm::vec3 Color;
	

	



	Terrain(glm::vec2 pos, glm::vec2 size, const char* terrainClass, glm::vec3 color = glm::vec3(1.0f), float rotation = 0.0 );
	void Draw(SpriteRenderer& renderer,Texture2D sprite, Shader shader,
		glm::mat4 projection, glm::vec2 cameraPos);

};

