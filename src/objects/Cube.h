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
  Cube(const ObjectProperties& properties);

  void draw(const SceneInfo&) override;

protected:
  GLuint _firstTexture;
  GLuint _secondTexture;

  GLuint createTexture(const char* path);
};
