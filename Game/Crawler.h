#ifndef CRAWLER_H
#define CRAWLER_H


#include "Enemy.h"



class Crawler : public Enemy
{

public:

	
	Crawler(int id, glm::vec2 pos, glm::vec2 size, glm::vec2 hitbox);
	void UpdateAggro() override;
	void Update(float dt, Player& player) override;
	void Atack()override;
	void UpdatePatterns(GameObject Object) override;
	void UpdateCreepingPattern(GameObject Object) override;
	


};

#endif