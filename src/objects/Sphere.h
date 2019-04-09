#pragma once

#include "RenderObject.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

extern float sphereVertices[];
extern unsigned sphereIndices[];

class Sphere : public RenderObject
{
public:
  Sphere(const ObjectProperties& properties);

  void draw(const SceneInfo&) override;
};
