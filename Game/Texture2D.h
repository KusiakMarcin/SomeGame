#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <glad/glad.h>

// Klasa Texture2D przechowuje i konfiguruje teksturê w OpenGL.
class Texture2D
{
public:
    unsigned int ID;
    unsigned int Width, Height; // Wymiary (w pikselach)
    unsigned int Internal_Format; // Format obiektu tekstury (np. GL_RGB)
    unsigned int Image_Format; // Format wczytanego obrazu (np. GL_RGB)

    // Konfiguracja tekstury
    unsigned int Wrap_S; // Wrapping mode on S axis
    unsigned int Wrap_T; // Wrapping mode on T axis
    unsigned int Filter_Min; // Filtering mode if texture pixels < screen pixels
    unsigned int Filter_Max; // Filtering mode if texture pixels > screen pixels

    Texture2D();

    // Generuje teksturê z danych
    void Generate(unsigned int width, unsigned int height, unsigned char* data);

    // Binds the texture as the current active GL_TEXTURE_2D texture object
    void Bind() const;
};

#endif