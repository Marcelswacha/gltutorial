#pragma once

#include "Shader.h"

#include "material/Material.h"
#include "LightProperties.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

struct ObjectProperties
{
  Shader* shader;
  glm::vec3 position;
  Material material;

  float* vertexData;
  unsigned* vertexIndices;
};

struct SceneInfo
{
  glm::mat4 viewMatrix;
  glm::mat4 projectionMatrix;

  LightProperties lightProperties;
  glm::vec3 lightPos;

  glm::vec3 cameraPos;
};

struct RenderObject
{
  ObjectProperties properties;
  GLuint vertexArrayObject;

  RenderObject(const ObjectProperties& props)
    : properties(props)
    , vertexArrayObject(0)
  {}

  virtual ~RenderObject(){}

  virtual void draw(const SceneInfo&) {};
  virtual void update() {};
};
