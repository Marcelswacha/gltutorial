#pragma once

#include "RenderObject.h"

#include "material/Material.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

extern float cubeVertices[];

class Cube : public RenderObject
{
public:
  Cube(Shader* s, float* vertices, const glm::vec3& pos, const std::string& material = "gold");

  void draw(const RenderInfo&) override;

protected:
  GLuint _firstTexture;
  GLuint _secondTexture;
  glm::vec3 _position;

  GLuint createTexture(const char* path);
};
