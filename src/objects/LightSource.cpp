#include "LightSource.h"

#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>

LightSource::LightSource(Shader*s, const glm::vec3& pos)
  : RenderObject(s)
  , _position(pos)
{
  glGenVertexArrays(1, &vertexArrayObject);
  glBindVertexArray(vertexArrayObject);

  float vertex[] = { _position.x, _position.y, _position.z };

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float), vertex, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void LightSource::draw(const RenderInfo& info)
{
  glm::mat4 model = glm::mat4(1.f);
  model = glm::translate(model, _position);

  shader->use();
  shader->setMat4("model", model);
  shader->setMat4("view", info.viewMatrix);
  shader->setMat4("projection", info.projectionMatrix);

  glPointSize(6.0);
  glBindVertexArray(vertexArrayObject);
  glDrawArrays(GL_POINTS, 0, 1);
}
