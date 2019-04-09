#version 460 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;

struct Material
{
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

uniform Material material;

void main()
{
  // ambient
  vec3 ambient = lightColor * material.ambient;

  // diffuse
  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(lightPos - FragPos);
  float diff = max(dot(lightDir, norm), 0.0f);
  vec3 diffuse = lightColor * (diff * material.diffuse);

  // specular
  vec3 viewDir = normalize(cameraPos - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
  vec3 specular = lightColor * (spec * material.specular);

  FragColor = vec4(ambient + diffuse + specular, 1.f);
}