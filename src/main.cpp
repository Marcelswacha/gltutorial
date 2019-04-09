
#include "application/GLApplication.h"
#include "objects/Cube.h"
#include "objects/Sphere.h"
#include "objects/LightSource.h"
#include "Shader.h"
#include "material/Material.h"

#include <helpers/RootDir.h>

#include <iostream>

static const int winWidth = 1200;
static const int winHeight = 800;

glm::vec3 cubePositions[] = {
  glm::vec3(1.0f,  2.0f,  1.0f),
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

    Shader cubeShader( (std::string(ROOT_DIR) + "res/shaders/MaterialVS.vs").c_str(),
                   (std::string(ROOT_DIR) + "res/shaders/MaterialFS.fs").c_str() );

    Shader lightShader( (std::string(ROOT_DIR) + "res/shaders/LightSourceVS.vs").c_str(),
        (std::string(ROOT_DIR) + "res/shaders/LightSourceFS.fs").c_str() );

//    LightProperties lightProps(
//      glm::vec3{1.f, 0.f, 0.f},
//      glm::vec3{0.f, 1.f, 0.f},
//      glm::vec3{0.f, 0.f, 1.f}
//    );
    LightProperties lightProps;

    app.addLightSource(new LightSource(
        lightProps,
        new Sphere(ObjectProperties{&lightShader, {0.f, 0.f, 0.f}, Material(), sphereVertices, sphereIndices})
    ));

    const Material& gold = Materials["gold"];
    const Material& silver = Materials["silver"];
    const Material& emerald = Materials["emerald"];
    for (int i = 0; i < 10; ++i) {
      if (i % 2 == 0) {
        app.addRenderObject(new Cube(ObjectProperties{&cubeShader, cubePositions[i], gold, cubeVertices}));
      }
      else if (i % 3 == 0) {
        app.addRenderObject(new Cube(ObjectProperties{&cubeShader, cubePositions[i], emerald, cubeVertices}));
      }
      else {
        app.addRenderObject(new Cube(ObjectProperties{&cubeShader, cubePositions[i], silver, cubeVertices}));
      }
    }

    app.run();
  }
  catch (const std::exception& e) {
    std::cout << e.what();
    return -1;
  }


  return 0;
}
