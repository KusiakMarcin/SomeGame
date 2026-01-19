#include "GameObject.h"


GameObject::GameObject(glm::vec2 pos, glm::vec2 size, bool isMovable, float rotation, bool isPhisical,bool isGroudned)
	:Position(pos), Size(size), Rotation(rotation), IsPhisical(isPhisical), Velocity(glm::vec2(0.0f, 0.0f))
{
	
}



GameObject::~GameObject()
{

	

}

