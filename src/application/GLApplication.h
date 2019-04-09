#pragma once

#include "application/Camera.h"
#include "objects/LightSource.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

class RenderObject;

struct AppInfo
{
  const char* windowName;
  int width;
  int height;
};

class GLApplication
{
public:
  GLApplication(const AppInfo& info);
  ~GLApplication();

  void run();
  void render();
  void processInput();

  void addRenderObject(RenderObject* object);
  void addLightSource(LightSource* light);

  void mouseCallback(GLFWwindow* window, double xpos, double ypos);
  void scrollCallback(GLFWwindow* window, double xOff, double yOff);
  void framebufferSizeCallback(GLFWwindow* window, int w, int h);
  void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

private:
  GLFWwindow* _window;
  int _winWidth;
  int _winHeight;
  Camera _camera;
  bool _isMousePressed;
  double _startX;
  double _startY;
  std::vector<RenderObject*> _renderObjects;
  std::vector<LightSource*> _lights;
};
