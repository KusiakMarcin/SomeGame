#ifndef INTERFACE_H
#define INTERFACE_H

#include <vector>
#include "SpriteRenderer.h"
#include "Texture2D.h"
#include "Shader.h"
#include "Player.h"*

class Interface
{
public:
    glm::vec2 Position; 
    glm::vec2 IconSize; 
    float Spacing;      

    Interface(glm::vec2 pos = glm::vec2(20.0f, 20.0f), glm::vec2 iconSize = glm::vec2(30.0f, 30.0f));

    // G³ówna metoda rysuj¹ca ca³y interfejs
    void DrawHUD(SpriteRenderer& renderer, Shader shader, Player& player,
        Texture2D& heartTex, glm::mat4 projection);

private:
    // Pomocnicza metoda do rysowania pojedynczych elementów statycznych
    void drawStaticElement(SpriteRenderer& renderer, Shader shader, Texture2D& tex,
        glm::vec2 pos, glm::vec2 size, glm::mat4 projection, glm::vec3 color);
};

#endif

