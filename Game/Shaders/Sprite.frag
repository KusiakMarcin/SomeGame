#version 330 
out vec4 FragColor;


in vec2 TexCoords;
in vec3 ShiftColor;

uniform sampler2D ourTexture;

void main()
{
	
	FragColor = texture(ourTexture, TexCoords) * vec4(ShiftColor,1.0f);

}