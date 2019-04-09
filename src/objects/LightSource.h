#pragma once

#include "RenderObject.h"

class LightSource
{
public:
  LightProperties lightProperties;

  LightSource(const LightProperties& lightProps = LightProperties(), RenderObject* obj = nullptr);

  glm::vec3 getPosition() const;
  void draw(const SceneInfo&);

protected:
  RenderObject* _renderObject;
};
