#include "Inteligent.h"


Inteligent::Inteligent(int id, glm::vec2 pos, glm::vec2 size, glm::vec2 hitbox)
	:	Unit(id,pos,size,hitbox)
{
	Updated = false;
}





Inteligent::Inteligent()
{

	;

}

void Inteligent::UpdatePatterns(GameObject ground)
{

	;
}
void Inteligent::UpdateCreepingPattern(GameObject ground)
{

	;

}

void Inteligent::UpdateAggro()
{

	AggroCenter = this->Position + this->Size / 2.0f;


}




