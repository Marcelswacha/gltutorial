#pragma once
#include <glm/glm.hpp>

#include <map>
#include <string>

struct Material
{
  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;
  float shininess;
};

extern std::map<std::string, Material> Materials;
