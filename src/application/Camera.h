#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <algorithm>
#include <iostream>

struct Camera
{
  glm::vec3 pos;
  glm::vec3 front;
  glm::vec3 up;
  float speed;
  float yaw;
  float pitch;
  float fov;

  Camera()
    : pos(0, 0, 3)
    , front(0, 0, -1)
    , up(0, 1, 0)
    , speed(0.05f)
    , yaw(-90.f)
    , pitch(0)
    , fov(45.f)
    , _lastYaw(yaw)
    , _lastPitch(pitch)
  {}

  glm::mat4 getView() const
  {
    return glm::lookAt(pos, pos + front, up);
  }


  void updateFrontPress(float xOff, float yOff)
  {
    yaw = _lastYaw + xOff;

    pitch = _lastPitch + yOff;
    pitch = std::max(-89.f, std::min(89.f, pitch));

    glm::vec3 f;
    f.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    f.y = sin(glm::radians(pitch));
    f.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

    front = glm::normalize(f);
  }

  void updateFrontRelease()
  {
    _lastYaw = yaw;
    _lastPitch = pitch;
  }

private:
  float _lastYaw;
  float _lastPitch;
};
