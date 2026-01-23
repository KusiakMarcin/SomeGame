#include "Interface.h"

Interface::Interface(glm::vec2 pos, glm::vec2 iconSize)
    : Position(pos), IconSize(iconSize), Spacing(10.0f)
{
}

void Interface::DrawHUD(SpriteRenderer& renderer, Shader shader, Player& player,
    Texture2D& heartTex, glm::mat4 projection)
{
    
    for (int i = 0; i < player.HP; i++)
    {
        glm::vec2 heartPos = this->Position + glm::vec2((this->IconSize.x + Spacing) * i, 0.0f);

        renderer.DrawSprite(projection, glm::vec2(0.0f), heartTex, shader,
            heartPos, 0, this->IconSize, 0.0f, glm::vec3(1.0f));
    }

    
}