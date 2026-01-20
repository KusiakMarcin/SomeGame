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

float clamp(float value, float min, float max) {
    return std::max(min, std::min(max, value));
}


bool Phisics::CheckColision(GameObject Object1, GameObject Object2)
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

bool Phisics::CheckColision(Projectile Object1, Unit Object2)
{
    if (Object1.SourceID != 1 && Object2.ID != 1) return false;

    if(Object2.IsPhisical && Object1.SourceID != Object2.ID && Object2.NotVunerable <= 0.0)
    {
        float CenterX = Object1.Position.x + Object1.AxisXShift;
        float CenterY = Object1.Position.y + Object1.Radius;

        

        glm::vec2 CenterProjectile(CenterX, CenterY);

        CenterX = Object2.Position.x + (Object2.Size.x-Object2.Hitbox.x) /2;
        CenterY = Object2.Position.y + (Object2.Size.y-Object2.Hitbox.y) /2;
        
            //jesli srodek kola jest wewnatrz
        /*bool cond1 = std::abs(CenterProjectile.x - (Object2.Position.x + Object2.Size.x / 2.0));
        bool cond2 = std::abs(CenterProjectile.y - (Object2.Position.y + Object2.Size.y / 2.0));
        if (cond1 && cond2) return true;*/

        glm::vec2 CenterUnit(CenterX, CenterY);

        glm::vec2 delta = CenterProjectile - CenterUnit;

        
        float clampY = clamp(delta.y, -Object2.Size.y / 2, +Object2.Size.y / 2);
        float clampX = clamp(delta.x, -Object2.Size.x / 2, +Object2.Size.x / 2);


        glm::vec2 ToClosest = CenterUnit + glm::vec2(clampX, clampY);
        delta = ToClosest - CenterProjectile;
        return glm::length(delta) < Object1.Radius;
            


        
    
    }
    return false;


}

bool Phisics::CheckColision(Projectile Object1, Terrain Object2)
{


    if (Object2.IsPhisical)
    {
        float CenterX = Object1.Position.x + Object1.AxisXShift;
        float CenterY = Object1.Position.y + Object1.Radius;



        glm::vec2 CenterProjectile(CenterX, CenterY);

        CenterX = Object2.Position.x + Object2.Size.x / 2.0;
        CenterY = Object2.Position.y + Object2.Size.y / 2.0;


        /*bool cond1 = (std::abs(CenterProjectile.x - (Object2.Position.x + Object2.Size.x / 2.0)))>Object2.Size.x/2;
        bool cond2 = (std::abs(CenterProjectile.y - (Object2.Position.y + Object2.Size.y / 2.0)))>Object2.Size.y/2;
        if (cond1 && cond2) return true;*/

        glm::vec2 CenterUnit(CenterX, CenterY);

        glm::vec2 delta = CenterProjectile - CenterUnit;

       

        float clampY = clamp(delta.y, -Object2.Size.y / 2.0, +Object2.Size.y / 2.0);
        float clampX = clamp(delta.x, -Object2.Size.x / 2.0, +Object2.Size.x / 2.0);

        glm::vec2 ToClosest = CenterUnit + glm::vec2(clampX, clampY);
        delta = ToClosest - CenterProjectile;
        return glm::length(delta) < Object1.Radius;





    }
    return false;


}

void Phisics::ResolveColision(Unit& MovableObject, GameObject& Terrain)
{
    float OverlapX, OverlapY;
    bool SideX, SideY;
    SideX = MovableObject.Position.x < Terrain.Position.x;
    SideY = MovableObject.Position.y < Terrain.Position.y;
    if (SideX)
        OverlapX = std::abs(MovableObject.Position.x + MovableObject.Size.x - Terrain.Position.x);
    else
        OverlapX = std::abs(Terrain.Position.x + Terrain.Size.x - MovableObject.Position.x);
    if (SideY)
        OverlapY = std::abs(MovableObject.Position.y + MovableObject.Size.y - Terrain.Position.y);
    else
        OverlapY = std::abs(Terrain.Position.y + Terrain.Size.y - MovableObject.Position.y);

    if (OverlapX < OverlapY)
    {
        if (SideX)
        {
            MovableObject.Position.x = Terrain.Position.x - MovableObject.Size.x;
            if (MovableObject.Velocity.x > 0.0f)MovableObject.Velocity.x = 0.0f;

        }
        else
        {
            MovableObject.Position.x = Terrain.Position.x + Terrain.Size.x;
            if (MovableObject.Velocity.x < 0.0f)MovableObject.Velocity.x = 0.0f;
        }
    }
    else
    {
        if (SideY)
        {
            MovableObject.Position.y = Terrain.Position.y - MovableObject.Size.y;
            if (MovableObject.Velocity.y > 0.0f)MovableObject.Velocity.y = 0.0f;
            MovableObject.IsGrounded = true;
        }
        else
        {
            MovableObject.Position.y = Terrain.Position.y + Terrain.Size.y;
            if (MovableObject.Velocity.y < 0.0f)MovableObject.Velocity.y = 0.0f;
        }
    }



}


void Phisics::ResolveColision(Projectile& Object1, Unit& Object2) 
{
    
    Object2.HP--;
    //Object2.Bounce()
    

}

void Phisics::ResolveColision(Projectile& Object1, GameObject& Object2)
{
    //Object1.obj1ExplosiobAnimationOrSomeShit()
    ;

}
