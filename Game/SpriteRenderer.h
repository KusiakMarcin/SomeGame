#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "Texture2D.h" // Zak³adamy, ¿e masz klasê Texture/Texture2D
#include "Shader.h"  // Zak³adamy, ¿e masz klasê Shader

class SpriteRenderer
{
private:
    // Stan renderera
    unsigned int quadVAO; // Vertex Array Object
    unsigned int EBO;

        // Funkcja inicjalizuj¹ca bufory i wierzcho³ki
    void initRenderData();
public:
    // Konstruktor (inicjalizuje shadery i geometriê)
    SpriteRenderer(Shader& shader);
    // Destruktor
    ~SpriteRenderer();

    // G³ówna funkcja rysuj¹ca
    // texture: obiekt tekstury do narysowania
    // position: pozycja w œwiecie (lewy górny róg)
    // size: rozmiar sprite'a w pikselach
    // rotate: k¹t obrotu w stopniach
    // color: kolor tintu (domyœlnie bia³y - brak zmiany)
    
    void DrawSprite(glm::mat4 projection, Texture2D& texture, Shader shader, 
        glm::vec2 position,
        glm::vec2 size = glm::vec2(10.0f, 10.0f),
        float rotate = 0.0f,
        glm::vec3 color = glm::vec3(1.0f));


    void DrawSpriteTerrain(glm::mat4 projection,Texture2D& texture,Shader shader, glm::vec2 position,
        glm::vec2 size = glm::vec2(10.0f, 10.0f),
        float rotate = 0.0f,
        glm::vec3 color = glm::vec3(1.0f));

    /*void DrawAnimation(Texture2D& texture, glm::vec2 position
        glm::vec2 size = glm::vec2(10.0f, 10.0f),
        float rotate = 0.0f,
        glm::vec3 color = glm::vec3(1.0f));*/
    
    glm::vec2 Tiling(glm::vec2 size, float tileSize = 50.0f);
    
};

#endif