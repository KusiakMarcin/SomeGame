#include "GameObject.h"


GameObject::GameObject(glm::vec2 pos, glm::vec2 size, float rotation, bool isPhisical)
	:Position(pos), Size(size), Rotation(rotation), IsPhisical(isPhisical)
{
	
}



GameObject::~GameObject()
{

	

}

