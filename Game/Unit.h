#include "GameObject.h"


class Unit : public GameObject
{
public:
	
	int ID;
	bool IsGrounded;
	float NotVunerable;
	bool IsBoss;
	bool IsMovable;
	int HP;
	glm::vec2 Hitbox;
	glm::vec2 Velocity;
	Unit(int id, glm::vec2 pos, glm::vec2 size,glm::vec2 hitbox,
		bool isMovable = true, bool isGrounded = false, float rotation = 0.0f);



};

