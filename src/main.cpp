
#include "application/GLApplication.h"
#include "objects/Cube.h"
#include "Shader.h"

#include <helpers/RootDir.h>

#include <iostream>

static const int winWidth = 1200;
static const int winHeight = 800;

glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};

int main()
{
  try {
    GLApplication app(AppInfo{"Learn OpenGL", winWidth, winHeight});

    Shader shader( (std::string(ROOT_DIR) + "res/shaders/CubeVS.vs").c_str(),
                   (std::string(ROOT_DIR) + "res/shaders/CubeFS.fs").c_str() );

    for (int i = 0; i < 10; ++i) {
      app.addRenderObject(new Cube(&shader, cubeVertices, cubePositions[i]));
    }

    app.run();
  }
  catch (const std::exception& e) {
    std::cout << e.what();
    return -1;
  }


  return 0;
}
