#pragma once

#include <glm/glm.hpp>

struct LightProperties
{
  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;

  LightProperties()
    : ambient(1.f, 1.f, 1.f)
    , diffuse(1.f, 1.f, 1.f)
    , specular(1.f, 1.f, 1.f)
    {}

  LightProperties(const glm::vec3& a, const glm::vec3& d, const glm::vec3& s)
    : ambient(a)
    , diffuse(d)
    , specular(s)
    {}
};
