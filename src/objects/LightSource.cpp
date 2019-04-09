#include "LightSource.h"

#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>

LightSource::LightSource(const LightProperties& lightProps, RenderObject* obj)
  : lightProperties(lightProps)
  , _renderObject(obj)
{
}

glm::vec3 LightSource::getPosition() const
{
  return _renderObject->properties.position;
}
void LightSource::draw(const SceneInfo& info)
{
  if (_renderObject != nullptr) {
    _renderObject->draw(info);
  }
}
