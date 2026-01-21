#include "TextRenderer.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <gtc/matrix_transform.hpp>
#include <iostream>

/**
 * @brief Konstruktor rendereru tekstu.
 */
TextRenderer::TextRenderer(unsigned int width, unsigned int height)
{
    TextShader = ResourceManager::LoadShader(
        "text.vs", "text.frag", nullptr, "Text"
    );

    glm::mat4 projection = glm::ortho(
        0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f
    );

    TextShader.Use();
    TextShader.SetMatrix4("projection", projection);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Dynamiczny bufor na wierzcho³ki znaków
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0, 4, GL_FLOAT, GL_FALSE,
        4 * sizeof(float),
        reinterpret_cast<void*>(0)
    );

    glBindVertexArray(0);
}

/**
 * @brief £aduje czcionkê i generuje tekstury znaków.
 */
void TextRenderer::Load(const std::string& font, unsigned int fontSize)
{
    FT_Library ft;
    FT_Face face;

    if (FT_Init_FreeType(&ft))
    {
        std::cerr << "ERROR::FREETYPE: Nie mo¿na zainicjalizowaæ biblioteki\n";
        return;
    }

    if (FT_New_Face(ft, font.c_str(), 0, &face))
    {
        std::cerr << "ERROR::FREETYPE: Nie mo¿na wczytaæ czcionki\n";
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, fontSize);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // £adujemy podstawowy zestaw ASCII
    for (unsigned char c = 0; c < 128; c++)
    {
        FT_Load_Char(face, c, FT_LOAD_RENDER);

        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<unsigned int>(face->glyph->advance.x)
        };

        Characters.insert({ c, character });
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

/**
 * @brief Renderuje tekst znak po znaku.
 */
void TextRenderer::RenderText(const std::string& text,
    float x, float y,
    float scale,
    const glm::vec3& color)
{
    TextShader.Use();
    TextShader.SetVector3f("textColor", color);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    for (char c : text)
    {
        const Character& ch = Characters[c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;

        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };

        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (ch.Advance >> 6) * scale;
    }

    glBindVertexArray(0);
}
