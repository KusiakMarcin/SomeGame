#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <vector>



// Instancjacja statycznych map
std::map<std::string, Texture2D> ResourceManager::Textures;
std::map<std::string, Shader> ResourceManager::Shaders;

ResourceManager &ResourceManager::getInstance()
{
    static ResourceManager Instance;
    return Instance;
}

Shader ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name)
{
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
    return Shaders[name];
}

Texture2D ResourceManager::LoadTexture(const char* file, bool alpha, std::string name, unsigned int wrap)
{
    Textures[name] = loadTextureFromFile(file, alpha,wrap);
    return Textures[name];
}

Texture2D ResourceManager::GetTexture(std::string name)
{
    return Textures[name];
}

void ResourceManager::Clear()
{
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;

    try {
        // Otwieramy pliki TYLKO RAZ przez konstruktor
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;

        if (!vertexShaderFile.is_open() || !fragmentShaderFile.is_open()) {
            std::cout << "ERROR::SHADER: Could not open file: " << vShaderFile << " or " << fShaderFile << std::endl;
        }

        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

        // Debug: SprawdŸmy czy kod nie jest pusty
        if (vertexCode.empty()) {
            std::cout << "SHADER: Vertex shader file is empty or not read" << std::endl;
        }

        if (gShaderFile != nullptr) {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryCode = gShaderStream.str();
        }
    } 
    catch (std::exception e) {
        std::cout << "SHADER: Failed to read shader files: " << e.what() << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    const char* gShaderCode = geometryCode.c_str();

    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const char* file, bool alpha, unsigned int wrap)
{
    // Tworzenie obiektu tekstury
    Texture2D texture;
    if (alpha)
    {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }

    texture.Wrap_S = wrap;
    texture.Wrap_T = wrap;
    

    // Wczytywanie obrazka
    int width, height, nrChannels;

    // UWAGA: Aby to dzia³a³o, musisz mieæ bibliotekê stb_image.h
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);

    if(data)
    {
        texture.Generate(width, height, data);

        
    
    }
    else
    {
        std::cout << "failed to load texture"<<file<<"\n";
    }
    stbi_image_free(data);
    return texture;
    
}

