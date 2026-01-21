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

void SpriteRenderer::DrawSpriteTerrain(glm::mat4 projection,glm::vec2 cameraPos, Texture2D& texture,Shader shader, 
    glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color)
{
    // 1. Przygotowanie transformacji
    shader.Use();
    glm::vec2 TileCount = Tiling(size);
    shader.SetVector2f("ObjectSize", TileCount.x, TileCount.y, true); //dopasuj rozmiar do textcords, powtarza zamiast rozciagac teksture
    shader.SetMatrix4("projection", projection, true);
   
    // Skalowanie -> Obrót -> Translacja
    
    glm::mat4 model = glm::mat4(1.0f);

    // A. Przesuniêcie do pozycji docelowej
    model = glm::translate(model, glm::vec3(position, 0.0f));
    
    model = glm::translate(model, glm::vec3(cameraPos, 0.0f));

    // B. Obrót wokó³ œrodka sprite'a
    // Domyœlnie obrót jest wokó³ (0,0), czyli lewego górnego rogu.
    // ¯eby obracaæ wokó³ œrodka: przesuwamy œrodek do (0,0), obracamy, przesuwamy z powrotem.
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    
    
   
    model = glm::scale(model, glm::vec3(size, 1.0f));

    // 2. Ustawienie uniformów
    shader.SetMatrix4("model", model);
    
     
    // 3. Rysowanie
    glActiveTexture(GL_TEXTURE0);
    texture.Bind(); 

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteRenderer::DrawSpriteAnimation(glm::mat4 projection, glm::vec2 cameraPos,Texture2D& texture, Shader shader,
    glm::vec2 position, int frame, int frameCount,float frameWidth, int mirrored, glm::vec2 size, float rotate, glm::vec3 color)
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
    model = glm::translate(model, glm::vec3(cameraPos, 0.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f));
    
    // 2. Ustawienie uniformów
    shader.SetMatrix4("model", model);
    shader.SetVector3f("spriteColor", color);
    shader.SetVector2f("textOffset", frameWidth*(frame%frameCount), 0.0f);
    shader.SetVector2f("texScale", 1.0f, 1.0f);

    // 3. Rysowanie
    glActiveTexture(GL_TEXTURE0);
    texture.Bind(); // Zak³adamy metodê Bind() w klasie Texture2D

    switch (mirrored) {

    case NO_MIRROR:
        glBindVertexArray(this->quadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
        break;


    case MIRRORED_X:
        glBindVertexArray(this->quadVAOMirroredX);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
        break;
    case MIRRORED_Y:
        glBindVertexArray(this->quadVAOMirroredY);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
        break;
    }
}

void SpriteRenderer::DrawMenuSprite(glm::mat4 projection, Texture2D& texture, Shader shader,
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
    float tmp = static_cast<float>(i % 3);
    i++;
    std::cout << tmp << std::endl;
    shader.SetVector2f("texOffset", tmp, 0.0f);
    shader.SetVector2f("texScale", 1.0f, 1.0f);

    // 3. Rysowanie
    glActiveTexture(GL_TEXTURE0);
    texture.Bind(); // Zak³adamy metodê Bind() w klasie Texture2D

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}


void SpriteRenderer::DrawSprite(glm::mat4 projection,glm::vec2 cameraPos , Texture2D& texture, Shader shader,
    glm::vec2 position,int mirrored, glm::vec2 size, float rotate, glm::vec3 color)
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


    model = glm::translate(model, glm::vec3(cameraPos, 0.0f));
    
    // Domyœlnie obrót jest wokó³ (0,0), czyli lewego górnego rogu.
    // ¯eby obracaæ wokó³ œrodka: przesuwamy œrodek do (0,0), obracamy, przesuwamy z powrotem.
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    
    model = glm::scale(model, glm::vec3(size, 1.0f));
 

    // 2. Ustawienie uniformów
    shader.SetMatrix4("model", model);
    shader.SetVector3f("spriteColor", color);
    shader.SetVector2f("texScale", 1.0f, 1.0f);

    // 3. Rysowanie
    glActiveTexture(GL_TEXTURE0);
    texture.Bind(); // Zak³adamy metodê Bind() w klasie Texture2D

    switch (mirrored) {

    case NO_MIRROR:
        glBindVertexArray(this->quadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
        break;


    case MIRRORED_X:
        glBindVertexArray(this->quadVAOMirroredX);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
        break;
    case MIRRORED_Y:
        glBindVertexArray(this->quadVAOMirroredY);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
        break;
    }
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

   
   
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    // TexCoords (u,v)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    
    
    float verticesMirroredY[] = {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f
    };

    unsigned int VBOMirroredY;
    glGenVertexArrays(1, &this->quadVAOMirroredY);
    glGenBuffers(1, &VBOMirroredY);

    glBindBuffer(GL_ARRAY_BUFFER, VBOMirroredY);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesMirroredY), verticesMirroredY, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAOMirroredY);



    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    // TexCoords (u,v)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    

    float verticesMirroredX[] = {
        // pos      // tex
        0.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,

        0.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 0.0f
    };

    unsigned int VBOMirroredX;
    glGenVertexArrays(1, &this->quadVAOMirroredX);
    glGenBuffers(1, &VBOMirroredX);

    glBindBuffer(GL_ARRAY_BUFFER, VBOMirroredX);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesMirroredX), verticesMirroredX, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAOMirroredX);



    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    // TexCoords (u,v)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    
    glBindVertexArray(0);
}

glm::vec2 SpriteRenderer::Tiling(glm::vec2 size, float tileSize)
{
    return glm::vec2(size.x / tileSize, size.y / tileSize);
}

