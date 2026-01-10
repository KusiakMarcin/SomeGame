#include "SpriteRenderer.h"
#include <iostream>
unsigned int i = 0;
SpriteRenderer::SpriteRenderer(Shader& shader)
{
    
    this->initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::DrawSpriteTerrain(glm::mat4 projection, Texture2D& texture,Shader shader, 
    glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color)
{
    // 1. Przygotowanie transformacji
    shader.Use();
    glm::vec2 TileCount = Tiling(size);
    shader.SetVector2f("ObjectSize", TileCount.x, TileCount.y, true); //dopasuj rozmiar do textcords, powtarza zamiast rozciagac teksture
    shader.SetMatrix4("projection", projection, true);
    // Model Matrix - kolejnoœæ operacji jest kluczowa:
    // Skalowanie -> Obrót -> Translacja
    // (W kodzie piszemy odwrotnie, bo macierze mno¿y siê od prawej do lewej)
    glm::mat4 model = glm::mat4(1.0f);

    // A. Przesuniêcie do pozycji docelowej
    model = glm::translate(model, glm::vec3(position, 0.0f));
    
    

    // B. Obrót wokó³ œrodka sprite'a
    // Domyœlnie obrót jest wokó³ (0,0), czyli lewego górnego rogu.
    // ¯eby obracaæ wokó³ œrodka: przesuwamy œrodek do (0,0), obracamy, przesuwamy z powrotem.
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    
    
   
    model = glm::scale(model, glm::vec3(size, 1.0f));

    // 2. Ustawienie uniformów
    shader.SetMatrix4("model", model);
    /*shader.SetVector3f("spriteColor", color);*/

    // Jeœli u¿ywasz shadera z animacj¹ (sprite_anim.vs), warto ustawiæ domyœlne wartoœci
    // dla statycznych obiektów, ¿eby nie zniknê³y lub nie wyœwietli³y siê dziwnie.
    // Zak³adamy, ¿e shader ma te uniformy. Jeœli u¿ywasz prostego shadera, te linie zostan¹ zignorowane.
    /*shader.SetVector2f("texOffset", 0.0f, 0.0f);
    shader.SetVector2f("texScale", 1.0f, 1.0f);*/

    // 3. Rysowanie
    glActiveTexture(GL_TEXTURE0);
    texture.Bind(); // Zak³adamy metodê Bind() w klasie Texture2D

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteRenderer::DrawSprite(glm::mat4 projection,Texture2D& texture, Shader shader,
    glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color)
{
    // 1. Przygotowanie transformacji
    shader.Use();
    shader.SetMatrix4("projection", projection, true);

    // Model Matrix - kolejnoœæ operacji jest kluczowa:
    // Skalowanie -> Obrót -> Translacja
    // (W kodzie piszemy odwrotnie, bo macierze mno¿y siê od prawej do lewej)
    glm::mat4 model = glm::mat4(1.0f);

    // A. Przesuniêcie do pozycji docelowej
    model = glm::translate(model, glm::vec3(position, 0.0f));



    // B. Obrót wokó³ œrodka sprite'a
    // Domyœlnie obrót jest wokó³ (0,0), czyli lewego górnego rogu.
    // ¯eby obracaæ wokó³ œrodka: przesuwamy œrodek do (0,0), obracamy, przesuwamy z powrotem.
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    

    model = glm::scale(model, glm::vec3(size, 1.0f));

    // 2. Ustawienie uniformów
    shader.SetMatrix4("model", model);
    shader.SetVector3f("spriteColor", color);
    float tmp = static_cast<float>(i%3);
    i++;
    std::cout << tmp<<std::endl;
    shader.SetVector2f("texOffset", tmp, 0.0f);
    shader.SetVector2f("texScale", 1.0f, 1.0f);

    // 3. Rysowanie
    glActiveTexture(GL_TEXTURE0);
    texture.Bind(); // Zak³adamy metodê Bind() w klasie Texture2D

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteRenderer::initRenderData()
{
    // Konfiguracja wierzcho³ków dla prostok¹ta (Quad)
    // Format: pos.x, pos.y, tex.x, tex.y
    // U¿ywamy znormalizowanych wspó³rzêdnych (0 do 1), które potem przeskalujemy macierz¹ Model
    float vertices[] = {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    unsigned int VBO;
    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);

    // Atrybut 0: Pozycja (vec2, ale w shaderze vec3, wiêc zrzutujemy na xy)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    
    // POPRAWKA DO SHADERA:
    // Poniewa¿ vertices[] przechowuje {posX, posY, texX, texY}, musimy to odpowiednio zmapowaæ.

    // Pozycja (x,y)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    // TexCoords (u,v)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

glm::vec2 SpriteRenderer::Tiling(glm::vec2 size, float tileSize)
{
    return glm::vec2(size.x / tileSize, size.y / tileSize);
}