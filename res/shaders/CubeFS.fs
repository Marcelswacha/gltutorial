#version 460 core
out vec4 FragColor;
  
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D firstTexture;
uniform sampler2D secondTexture;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;

void main()
{
  float ambient = 0.1f;
  
  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(lightPos - FragPos);
  float diffuseStrenght = 0.25;
  float diffuse = diffuseStrenght * max(dot(lightDir, norm), 0.0f);
  
  vec3 viewDir = normalize(cameraPos - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float specularStrenght = 0.65f;
  float specular = specularStrenght * pow(max(dot(viewDir, reflectDir), 0.0f), 128);
  
  float lightF = ambient + diffuse + specular;
  FragColor = mix(texture(firstTexture, TexCoord), texture(secondTexture, TexCoord), 0.5f) * vec4(lightF * lightColor, 1.f);
}