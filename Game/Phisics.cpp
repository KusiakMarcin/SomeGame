#include "Phisics.h"

void HandleColision(GameObject& Object1, GameObject& Object2, bool X, bool Y)
{


}

bool AABB(float PositionA, float sizeA, float PositionB, float sizeB)
{

	return PositionA + sizeA >= PositionB + sizeB;

}

Phisics::Phisics(float gravity)
	: Gravity(gravity)
{




}



bool Phisics::CheckColision(GameObject& Object1, GameObject& Object2)
{
	bool axisX, axisY;
	
	
	if (Object1.Position.x < Object2.Position.x) axisX = AABB(
		Object1.Position.x,
		Object1.Size.x,
		Object2.Position.x,
		0.0f);
	else 
		axisX = AABB(
		Object2.Position.x,
		Object2.Size.x,
		Object1.Position.x,
		0.0f);


	if (Object1.Position.y< Object2.Position.y) axisY = AABB(
			Object1.Position.y,
			Object1.Size.y,
			Object2.Position.y,
			0.0f);
	else
		axisY = AABB(
			Object2.Position.y,
			Object2.Size.y,
			Object1.Position.y,
			0.0f);
	return axisX&&axisY;

}





