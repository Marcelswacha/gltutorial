#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>

class Shader
{
public:
  // constructor reads and builds the shader
  Shader(const char* vertexPath, const char* fragmentPath);

  // use/activate the shader
  void use();

  // utility uniform functions
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  void setVec3f(const std::string& name, const glm::vec3& value) const;
  void setMat4(const std::string& name, const glm::mat4& transform) const;

  GLuint getID() const;

private:
  GLuint _id;
};
