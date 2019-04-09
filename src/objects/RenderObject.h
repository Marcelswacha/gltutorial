#pragma once

#include "Shader.h"

#include "material/Material.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

struct RenderInfo
{
  glm::mat4 viewMatrix;
  glm::mat4 projectionMatrix;

  glm::vec3 ligthColor;
  glm::vec3 lightPos;

  glm::vec3 cameraPos;
};

struct RenderObject
{
  Shader* shader;
  std::string materialName;
  GLuint vertexArrayObject;

  RenderObject(Shader* s, const std::string& material = "gold")
    : shader(s)
    , materialName(material)
  {}

  virtual ~RenderObject(){}

  virtual void draw(const RenderInfo&) {};
  virtual void update() {};
};
