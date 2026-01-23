#ifndef FLYER_H
#define FLYER_H

#include "Enemy.h"

class Flyer : public Enemy
{
public:
    // Prêdkoœæ pionowa (np. dla efektu lewitacji/falowania)
    float HoverSpeed;
    float HoverAmount;
    float InitialY;

    Flyer(int id, glm::vec2 pos, glm::vec2 size, glm::vec2 hitbox);

    // Nadpisujemy Update, aby zmieniæ logikê ruchu (latanie zamiast chodzenia)
    void Update(float dt, Player& player) override;
    void UpdateAggro()override;
    void UpdatePatterns(GameObject Object) override;
    void Atack()override;
    void UpdateCreepingPattern(GameObject ground) override;
};

#endif