#ifndef INTELIGENT_H
#define INTELIGENT_H

#include "Unit.h"




class Inteligent : public Unit
{

public:

	
	bool IsAgressive;
	bool IsCreeping;
	bool IsSpiky;
	bool IsBoss;
	bool Updated;

	
	glm::vec2 Aggro;
	glm::vec2 AggroCenter;
	glm::vec2 CreepingRange;

	glm::vec2 AtackDirection;

	Inteligent(int id, glm::vec2 pos, glm::vec2 size, glm::vec2 hitbox);
	Inteligent();

	//virtual void AtackPattern();
	//void Atack();

	virtual void UpdatePatterns(GameObject Object) ;

	virtual void UpdateCreepingPattern(GameObject ground);
	virtual void UpdateAggro();
protected:
	

	
	
	

};

#endif

