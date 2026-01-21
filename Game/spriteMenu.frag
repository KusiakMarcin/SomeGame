#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColor;

void main()
{    
    // Mno¿ymy kolor tekstury przez kolor ustawiony w kodzie C++ (spriteColor)
    color = vec4(spriteColor, 1.0) * texture(image, TexCoords);
}