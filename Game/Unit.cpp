#include "Unit.h"

Unit::Unit(int id, glm::vec2 pos, glm::vec2 size, glm::vec2 hitbox, bool isMovable, bool isGrounded,float rotation)
	:GameObject(pos,size,rotation), ID(id), IsGrounded(isGrounded),
	Velocity(glm::vec2(0.0f,0.0f)), Hitbox(hitbox), IsMovable(isMovable),NotVunerable(0.0f)
{


}
