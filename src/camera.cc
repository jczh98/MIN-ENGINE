// MIT License
// 
// Copyright (c) 2018-2019, neverfelly <neverfelly@gmail.com>
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "camera.h"

namespace min::engine {

Camera::Camera(float aspect, Vector3f pos, Vector3f up, float yaw, float pitch)
    : direction_(Vector3f(0.0f, 0.0f, -1.0f)),
      speed_(2.5f),
      mouse_sensitivity_(0.01f),
      fov_(45.0f) {
  position_ = pos;
  world_up_ = up;
  yaw_ = yaw;
  pitch_ = pitch;
  this->aspect = aspect;
  UpdateCameraVectors();
}

void Camera::ProcessKeyboard(min::engine::Direction direction, min::engine::TimeStep ts) {
  float velocity = speed_ * ts;
  switch (direction) {
    case FORWARD: position_ += direction_ * velocity;
      break;
    case BACKWARD: position_ -= direction_ * velocity;
      break;
    case LEFT: position_ -= right_ * velocity;
      break;
    case RIGHT: position_ += right_ * velocity;
      break;
  }
}

void Camera::ProcessMouseMovement(float x_offset, float y_offset, GLboolean constrain_pitch) {
  x_offset *= mouse_sensitivity_;
  y_offset *= mouse_sensitivity_;
  yaw_ += x_offset;
  pitch_ += y_offset;
  if (constrain_pitch) {
    pitch_ = std::min(pitch_, 89.0f);
    pitch_ = std::max(pitch_, -89.0f);
  }
  UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float y_offset) {
  if (fov_ >= 1.0f && fov_ <= 45.0f) fov_ -= y_offset;
  if (fov_ <= 1.0f) fov_ = 1.0f;
  if (fov_ >= 45.0f) fov_ = 45.0f;
}

void Camera::UpdateCameraVectors() {
  using namespace nf::math;
  Vector3f front;
  front.x() = std::cos(radians(yaw_)) * std::cos(radians(pitch_));
  front.y() = std::sin(radians(pitch_));
  front.z() = std::sin(radians(yaw_)) * std::cos(pitch_);
  direction_ = front.normalized();
  right_ = direction_.cross(world_up_).normalized();
  vector_up_ = right_.cross(direction_).normalized();
}

}
