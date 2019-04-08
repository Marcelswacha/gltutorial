#include "application/GLApplication.h"

#include "objects/RenderObject.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdexcept>

GLApplication* sApplicationInstance = nullptr;

static void sFramebufferSizeCallback(GLFWwindow* window, int w, int h)
{
  sApplicationInstance->framebufferSizeCallback(window, w, h);
}

static void sMouseCallback(GLFWwindow* window, double xpos, double ypos)
{
  sApplicationInstance->mouseCallback(window, xpos, ypos);
}

static void sScrollCallback(GLFWwindow* window, double xOff, double yOff)
{
  sApplicationInstance->scrollCallback(window, xOff, yOff);
}

static void sMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
  sApplicationInstance->mouseButtonCallback(window, button, action, mods);
}

GLApplication::GLApplication(const AppInfo& info)
  : _winWidth(info.width)
  , _winHeight(info.height)
  , _isMousePressed(false)
  , _startX(0.0)
  , _startY(0.0)
{
  // GLFW init
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // GLFWindow
  _window = glfwCreateWindow(_winWidth, _winHeight, info.windowName, nullptr, nullptr);
  if (_window == nullptr) {
    glfwTerminate();
    throw std::runtime_error("Failed to create GLFW window");
  }
  glfwMakeContextCurrent(_window);

  // GLAD init
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw std::runtime_error("Failed to initialize GLAD");
  }

  // Viewport
  glViewport(0, 0, _winWidth, _winHeight);

  glEnable(GL_DEPTH_TEST);

  // Register callbacks
  glfwSetFramebufferSizeCallback(_window, sFramebufferSizeCallback);
  glfwSetCursorPosCallback(_window, sMouseCallback);
  glfwSetScrollCallback(_window, sScrollCallback);
  glfwSetMouseButtonCallback(_window, sMouseButtonCallback);

  sApplicationInstance = this;
}

void GLApplication::run()
{
  while (!glfwWindowShouldClose(_window)) {
    processInput();

    render();

    glfwSwapBuffers(_window);
    glfwPollEvents();
  }
}

void GLApplication::processInput()
{
  if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(_window, GLFW_TRUE);
  }

  if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) {
    _camera.pos += _camera.speed * _camera.front;
  }
  if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS) {
    _camera.pos -= _camera.speed * _camera.front;
  }
  if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS) {
    _camera.pos -= glm::normalize(glm::cross(_camera.front, _camera.up)) + _camera.speed;
  }
  if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS) {
    _camera.pos += glm::normalize(glm::cross(_camera.front, _camera.up)) + _camera.speed;
  }
}

void GLApplication::render()
{
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glm::mat4 projection;
  projection = glm::perspective(glm::radians(_camera.fov), (float)_winWidth / _winHeight, 0.1f, 100.0f);
  const RenderInfo info{_camera.getView(), projection };

  for (RenderObject* object : _renderObjects) {
    object->update();
    object->draw(info);
  }
}

void GLApplication::addRenderObject(RenderObject* object)
{
  _renderObjects.push_back(object);
}

void GLApplication::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
  static const float sensitivity = 0.05;

  if (_isMousePressed) {
    float xoffset = _startX - xpos;
    float yoffset = ypos - _startY;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    _camera.updateFrontPress(xoffset, yoffset);
  }
}

void GLApplication::scrollCallback(GLFWwindow* window, double xOff, double yOff)
{
  _camera.fov -= yOff;
  _camera.fov = std::min(60.f, std::max(1.f, _camera.fov));
}

void GLApplication::framebufferSizeCallback(GLFWwindow* window, int w, int h)
{
  _winWidth = w;
  _winHeight = h;

  glViewport(0, 0, _winWidth, _winHeight);
}

void GLApplication::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
  if (button == GLFW_MOUSE_BUTTON_1) {
    if (action == GLFW_PRESS) {
      _isMousePressed = true;
      glfwGetCursorPos(window, &_startX, &_startY);
    }
    else {
      _isMousePressed = false;
      _camera.updateFrontRelease();
    }
  }
}

GLApplication::~GLApplication()
{
  glfwTerminate();
}
