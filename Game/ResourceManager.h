#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <glad/glad.h>

#include "Texture2D.h"
#include "Shader.h"

// Statyczna klasa singleton do zarz¹dzania zasobami (Tekstury, Shadery)
class ResourceManager
{


private:
    ResourceManager() {} // Prywatny konstruktor

    // Pomocnicze funkcje ³adowania
    
    static Shader    loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
    static Texture2D loadTextureFromFile(const char* file, bool alpha, unsigned int wrap = GL_REPEAT);


public:
    // Magazyny zasobów
    /*ResourceManager(ResourceManager const&) = delete;
    void operator = (ResourceManager const&) = delete;*/
    static std::map<std::string, Shader>    Shaders;
    static std::map<std::string, Texture2D> Textures;


    // £aduje (i kompiluje) shader z plików
    static Shader    LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
    // Pobiera za³adowany shader
    static Shader    GetShader(std::string name);

    // £aduje teksturê z pliku (Wymaga stb_image.h)
    static Texture2D LoadTexture(const char* file, bool alpha, std::string name, unsigned int wrap = GL_REPEAT);
    // Pobiera za³adowan¹ teksturê
    static Texture2D GetTexture(std::string name);
    static ResourceManager& getInstance();

    
    // Sprz¹ta pamiêæ
    static void      Clear();
};

#endif