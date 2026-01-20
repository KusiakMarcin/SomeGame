#pragma once
#include "Player.h"
#include "Terrain.h"
#include "Projectile.h"
class Phisics
{

public:

	Phisics(float gravity = 1600.0f);
	float Gravity;
	bool CheckColision(GameObject Object1, GameObject Object2);
	bool CheckColision(Projectile Object1, Unit Object2);
	bool CheckColision(Projectile Object1, Terrain Object2);
	

	
	void ResolveColision(Unit& MovableObject, GameObject& Terrain);
	void ResolveColision(Projectile& Object1, Unit& Object2);
	void ResolveColision(Projectile& Object1, GameObject& Object2);

	

};

