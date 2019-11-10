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

Camera::Camera(const Vector3f &position, const Vector3f &up, float yaw, float pitch)
    : front_(Vector3f(0, 0, -1)),
      movement_speed_(2.5f),
      mouse_sensitivity_(1.0f),
      zoom_(45.0f) {
  position_ = position;
  world_up_ = up;
  yaw_ = yaw;
  pitch_ = pitch;
  UpdateCamera();
}
void Camera::ProcessKeyboard(Direction direction, float delta_time) {
  float velocity = movement_speed_ * delta_time;
  switch (direction) {
    case FORWARD: position_ += front_ * velocity; break;
    case BACKWARD: position_ -= front_ * velocity; break;
    case RIGHT: position_ += right_ * velocity; break;
    case LEFT: position_ -= right_ * velocity; break;
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
  UpdateCamera();
}
void Camera::ProcessMouseScroll(float y_offset) {
  if (zoom_ >= 1.0f && zoom_ <= 45.0f) zoom_ -= y_offset;
  if (zoom_ <= 1.0f) zoom_ = 1.0f;
  if (zoom_ >= 45.0f) zoom_ = 45.0f;
}
void Camera::UpdateCamera() {
  // Calculate the new Front vector
  using namespace nf;
  Vector3f front;
  front.x() = cos(math::radians(yaw_)) * cos(math::radians(pitch_));
  front.y() = sin(math::radians(pitch_));
  front.z() = sin(math::radians(yaw_)) * cos(math::radians(pitch_));
  front_ = front.normalized();
  // Also re-calculate the Right and Up vector
  right_ = front_.cross(world_up_).normalized();
  up_ = right_.cross(front_).normalized();
}

}
