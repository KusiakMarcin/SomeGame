#pragma once
#include "Player.h"
#include "Terrain.h"
#include "Projectile.h"
class Phisics
{

public:

	Phisics(float gravity = 1600.0f);
	float Gravity;
	bool CheckColision(GameObject& Object1, GameObject& Object2);
	


};

