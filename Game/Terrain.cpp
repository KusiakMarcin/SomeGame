#include "Terrain.h"


Terrain::Terrain(glm::vec2 pos, glm::vec2 size, const char* terrainClass,glm::vec3 color, float rotation)
	: GameObject(pos, size, rotation), Color(color),TerrainClass(terrainClass)
{
	IsPhisical = true;
	isDestructable = false;
	isHarmful = false;

	if(terrainClass == "Dirt")
	{
		IsPhisical = true;
		isDestructable = false;
		isHarmful = false;
		
	}
	if (terrainClass == "Magma")
	{
		IsPhisical = true;
		isDestructable = false;
		isHarmful = true;

	}
	if (terrainClass == "Wood")
	{
		IsPhisical = true;
		isDestructable = true;
		isHarmful = false;

	}
	
	 
}

void Terrain::Draw(SpriteRenderer& renderer, Texture2D sprite,
	Shader shader,glm::mat4 projection,glm::vec2 cameraPos)
{
	
	
	renderer.DrawSpriteTerrain(projection, cameraPos 
		, sprite, shader,
		this->Position + glm::vec2(350.0f, 250.f),
		this->Size, this->Rotation, this->Color);
 }