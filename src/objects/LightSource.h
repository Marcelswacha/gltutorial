#pragma once

#include "RenderObject.h"

class LightSource : public RenderObject
{
public:
  LightSource(Shader* s, const glm::vec3& pos);

  void draw(const RenderInfo&) override;

protected:
  glm::vec3 _position;
};
