#include "Utils.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

unsigned createShader(const char* code, unsigned shaderType)
{
  unsigned shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &code, nullptr);
  glCompileShader(shader);

  // check for errors
  int success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetShaderInfoLog(shader, 512, nullptr, infoLog);
    std::cout << "Error compiling shader: " << infoLog << std::endl;
  }

  return shader;
}

unsigned createShaderProgram(const char* vertexShaderCode,
  const char* fragmentShaderCode)
{
  unsigned vertexShader = createShader(vertexShaderCode, GL_VERTEX_SHADER);
  unsigned fragmentShader = createShader(fragmentShaderCode, GL_FRAGMENT_SHADER);

  unsigned shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  int success;
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
    std::cout << "Shader program linking failed: " << infoLog;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return shaderProgram;
}


