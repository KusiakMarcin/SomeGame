#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include <map>
#include <string>
#include <glm.hpp>
#include <glad/glad.h>
#include "Shader.h"
#include "ResourceManager.h"

/**
 * @struct Character
 * @brief Reprezentuje pojedynczy znak czcionki za³adowanej przez FreeType.
 */
struct Character
{
    unsigned int TextureID;   ///< ID tekstury OpenGL z bitmap¹ znaku
    glm::ivec2 Size;          ///< Rozmiar znaku (w pikselach)
    glm::ivec2 Bearing;       ///< Przesuniêcie wzglêdem linii bazowej
    unsigned int Advance;     ///< Przesuniêcie kursora do nastêpnego znaku
};

/**
 * @class TextRenderer
 * @brief Renderer tekstu 2D oparty o FreeType i OpenGL.
 */
class TextRenderer
{
public:
    /**
     * @brief Tworzy renderer tekstu z projekcj¹ ortograficzn¹.
     * @param width Szerokoœæ okna
     * @param height Wysokoœæ okna
     */
    TextRenderer(unsigned int width, unsigned int height);

    /**
     * @brief £aduje czcionkê TrueType i generuje zestaw znaków ASCII.
     * @param font Œcie¿ka do pliku .ttf
     * @param fontSize Wysokoœæ czcionki w pikselach
     */
    void Load(const std::string& font, unsigned int fontSize);

    /**
     * @brief Renderuje tekst 2D na ekranie.
     * @param text Tekst do wyœwietlenia
     * @param x Pozycja X (piksele)
     * @param y Pozycja Y (piksele)
     * @param scale Skala tekstu
     * @param color Kolor tekstu
     */
    void RenderText(const std::string& text,
        float x, float y,
        float scale,
        const glm::vec3& color);

private:
    std::map<char, Character> Characters; ///< Mapa znaków ASCII
    Shader TextShader;                     ///< Shader do renderowania tekstu
    unsigned int VAO, VBO;                 ///< Bufory OpenGL
};

#endif