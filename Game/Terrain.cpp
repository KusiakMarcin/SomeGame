#include "Terrain.h"


Terrain::Terrain(glm::vec2 pos, glm::vec2 size,glm::vec3 color, float rotation) 
	: GameObject(pos, size, rotation), Color(color)
{
	 
}

void Terrain::Draw(SpriteRenderer& renderer, Texture2D sprite,
	Shader shader,glm::mat4 projection,glm::vec2 cameraPos)
{
	
	
	renderer.DrawSpriteTerrain(projection, cameraPos-glm::vec2(350.0f,250.f), sprite, shader, this->Position, this->Size, this->Rotation, this->Color);
 }