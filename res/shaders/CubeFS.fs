#version 460 core
out vec4 FragColor;
  
in vec2 TexCoord;

uniform sampler2D firstTexture;
uniform sampler2D secondTexture;

void main()
{
    FragColor = mix(texture(firstTexture, TexCoord), texture(secondTexture, TexCoord), 0.5f);
}