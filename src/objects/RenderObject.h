#pragma once

#include "Shader.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

struct RenderInfo
{
  glm::mat4 viewMatrix;
  glm::mat4 projectionMatrix;
};

struct RenderObject
{
  Shader* shader;
  GLuint vertexArrayObject;

  RenderObject(Shader* s)
    : shader(s)
  {}

  virtual ~RenderObject(){}

  virtual void draw(const RenderInfo&) {};
  virtual void update() {};
};
