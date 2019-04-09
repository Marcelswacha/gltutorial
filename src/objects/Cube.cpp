#include "Cube.h"

#include "material/Material.h"
#include "stb_image.h"

#include <helpers/RootDir.h>

#include <iostream>

float cubeVertices[] = {
  // position          // UV          // Normal
  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   0.0f,  0.0f, -1.0f,
  0.5f, -0.5f, -0.5f,  1.0f, 0.0f,    0.0f,  0.0f, -1.0f,
  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,    0.0f,  0.0f, -1.0f,
  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,    0.0f,  0.0f, -1.0f,
  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,    0.0f,  0.0f, -1.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,    0.0f,  0.0f, -1.0f,

  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,    0.0f,  0.0f, 1.0f,
  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,    0.0f,  0.0f, 1.0f,
  0.5f,  0.5f,  0.5f,  1.0f, 1.0f,    0.0f,  0.0f, 1.0f,
  0.5f,  0.5f,  0.5f,  1.0f, 1.0f,    0.0f,  0.0f, 1.0f,
  -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,    0.0f,  0.0f, 1.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,    0.0f,  0.0f, 1.0f,

  -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,    -1.0f,  0.0f, 0.0f,
  -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,    -1.0f,  0.0f, 0.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,    -1.0f,  0.0f, 0.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,    -1.0f,  0.0f, 0.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,    -1.0f,  0.0f, 0.0f,
  -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,    -1.0f,  0.0f, 0.0f,

  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,    1.0f,  0.0f, 0.0f,
  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,    1.0f,  0.0f, 0.0f,
  0.5f, -0.5f, -0.5f,  0.0f, 1.0f,    1.0f,  0.0f, 0.0f,
  0.5f, -0.5f, -0.5f,  0.0f, 1.0f,    1.0f,  0.0f, 0.0f,
  0.5f, -0.5f,  0.5f,  0.0f, 0.0f,    1.0f,  0.0f, 0.0f,
  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,    1.0f,  0.0f, 0.0f,

  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,    0.0f,  -1.0f, 0.0f,
  0.5f, -0.5f, -0.5f,  1.0f, 1.0f,    0.0f,  -1.0f, 0.0f,
  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,    0.0f,  -1.0f, 0.0f,
  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,    0.0f,  -1.0f, 0.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,    0.0f,  -1.0f, 0.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,    0.0f,  -1.0f, 0.0f,

  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,     0.0f,  1.0f, 0.0f,
  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,     0.0f,  1.0f, 0.0f,
  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,     0.0f,  1.0f, 0.0f,
  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,     0.0f,  1.0f, 0.0f,
  -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,     0.0f,  1.0f, 0.0f,
  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,     0.0f,  1.0f, 0.0f
};

Cube::Cube(const ObjectProperties& props)
  : RenderObject(props)
{
  // generate and bind VAO
  glGenVertexArrays(1, &vertexArrayObject);
  glBindVertexArray(vertexArrayObject);

  // generate, bind and copy VBO
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 288, properties.vertexData, GL_STATIC_DRAW);

  // set the vertex attributes pointers
  //position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // uv
//  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//  glEnableVertexAttribArray(1);

  // normals
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
  glEnableVertexAttribArray(2);

  _firstTexture = createTexture((std::string(ROOT_DIR) + "res/textures/container.jpg").c_str());
  _secondTexture = createTexture((std::string(ROOT_DIR) + "res/textures/awesomeface.png").c_str());

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Cube::draw(const SceneInfo& info)
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _firstTexture);

  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, _secondTexture);

  Shader* shader = properties.shader;
  shader->use();
  shader->setInt("firstTexture", 0);
  shader->setInt("secondTexture", 1);

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, properties.position);
  model = glm::rotate(model, glm::radians(100 * (float)glfwGetTime()), glm::vec3(0.0f, 1.0f, 1.0f));

  // 3d scene
  shader->setMat4("model", model);
  shader->setMat4("view", info.viewMatrix);
  shader->setMat4("projection", info.projectionMatrix);
  shader->setVec3f("cameraPos", info.cameraPos);

  // light
  shader->setVec3f("light.ambient",  info.lightProperties.ambient);
  shader->setVec3f("light.diffuse",  info.lightProperties.diffuse);
  shader->setVec3f("light.specular", info.lightProperties.specular);
  shader->setVec3f("light.position", info.lightPos );

  // materials
  Material material = properties.material;
  shader->setVec3f("material.ambient", material.ambient);
  shader->setVec3f("material.diffuse", material.diffuse);
  shader->setVec3f("material.specular", material.specular);
  shader->setFloat("material.shininess", material.shininess);

  glBindVertexArray(vertexArrayObject);
  glDrawArrays(GL_TRIANGLES, 0, 36);
}

GLuint Cube::createTexture(const char* path)
{
  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  // set the texture wrapping/filtering options (on the currently bound texture object)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int width, height, nrChannels;
  unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
  unsigned channelType = nrChannels == 3 ? GL_RGB : GL_RGBA;
  if (data != nullptr) {
    glTexImage2D(GL_TEXTURE_2D, 0, channelType, width, height, 0, channelType, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else {
    std::cout << "Failed to load texture data" << std::endl;
  }

  stbi_image_free(data);

  return texture;
}
