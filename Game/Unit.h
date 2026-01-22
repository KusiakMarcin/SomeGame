#ifndef UNIT_H
#define UNIT_H



#include "GameObject.h"


class Unit : public GameObject
{
public:
	
	int ID;
	
	bool IsGrounded;
	bool IsMovable;
	bool IsMoving;
	bool IsFacingLeft;
	bool IsKilled;
	float NotVunerable;
	float MoveSpeed;
	float Gravity;
	float JumpForce;
	float WasHit;

	
	int HP;
	
	
	
	
	glm::vec2 Hitbox;
	glm::vec2 Velocity;

	Unit(int id, glm::vec2 pos, glm::vec2 size,glm::vec2 hitbox,
		bool isMovable = true, bool isGrounded = false, float rotation = 0.0f);

	Unit();

};

#endif
