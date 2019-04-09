#include "Shader.h"
#include "Utils.h"

#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
  // Retrieve the vertex/fragment source code from filePath
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;

  // Ensure ifstream objects can throw exceptions:
  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    // open files
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);
    std::stringstream vShaderStream, fShaderStream;

    // read file's buffer contents into streams
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    // close file handlers
    vShaderFile.close();
    fShaderFile.close();

    // convert stream into string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  }
  catch (std::ifstream::failure& e) {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
  }

  _id = createShaderProgram(vertexCode.c_str(), fragmentCode.c_str());
}

void Shader::use()
{
  glUseProgram(_id);
}

void Shader::setBool(const std::string &name, bool value) const
{
  glUniform1i(glGetUniformLocation(_id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
  glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
  glUniform1f(glGetUniformLocation(_id, name.c_str()), value);
}

void Shader::setVec3f(const std::string& name, const glm::vec3& value) const
{
  glUniform3f(glGetUniformLocation(_id, name.c_str()), value.x, value.y, value.z);
}

void Shader::setMat4(const std::string& name, const glm::mat4& transform) const
{
  glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(transform));
}

GLuint Shader::getID() const
{
  return _id;
}
