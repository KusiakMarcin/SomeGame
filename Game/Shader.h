#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

// Klasa Shader odpowiada za kompilacjê i zarz¹dzanie programami GLSL
class Shader
{
public:
    unsigned int ID; // ID programu shaderowego

    Shader() {}

    // Ustawia bie¿¹cy shader jako aktywny
    Shader& Use();

    // Kompiluje shader z podanego kodu Ÿród³owego (vertex, fragment, geometry)
    void Compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr);

    // Funkcje pomocnicze (Utility functions)
    void SetFloat(const char* name, float value, bool useShader = false);
    void SetInteger(const char* name, int value, bool useShader = false);
    void SetVector2f(const char* name, float x, float y, bool useShader = false);
    void SetVector2f(const char* name, const glm::vec2& value, bool useShader = false);
    void SetVector3f(const char* name, float x, float y, float z, bool useShader = false);
    void SetVector3f(const char* name, const glm::vec3& value, bool useShader = false);
    void SetVector4f(const char* name, float x, float y, float z, float w, bool useShader = false);
    void SetVector4f(const char* name, const glm::vec4& value, bool useShader = false);
    void SetMatrix4(const char* name, const glm::mat4& matrix, bool useShader = false);

private:
    // Sprawdza b³êdy kompilacji/linkowania
    void checkCompileErrors(unsigned int object, std::string type);
};

#endif