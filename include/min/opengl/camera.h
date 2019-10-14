/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include <min/math/math.h>
#include <GL/glew.h>


MIN_NAMESPACE_BEGIN
namespace gl {

enum Direction {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
};

class Camera {
 public:
  Camera(Vector3f pos = Vector3(0.0, 0.0, 0.0),
         Vector3f up = Vector3(0.0, 1.0, 0.0),
         float yaw = -90.f, float pitch = 0.0f) : front_(Vector3f(0.0f, 0.0f, -1.0f)),
                                                  speed_(2.5f), mouse_sensitivity_(0.1f), zoom(45.0f) {
    this->position_ = pos;
    this->worldup_ = up;
    this->yaw_ = yaw;
    this->pitch_ = pitch;
    UpdateCameraVectors();
  }
  Camera(Float pos_x, Float pos_y, Float pos_z, Float up_x, Float up_y, Float up_z, Float yaw, Float pitch) : Camera(Vector3(pos_x, pos_y, pos_z), Vector3(up_x, up_y, up_z), yaw, pitch) {}

  Matrix4 GetViewMatrix() { return math::LookAt(position_, position_ + front_, up_);}
  void ProcessKeyboard(Direction direction, Float delta_time) {
    Float velocity = speed_ * delta_time;
    switch (direction) {
      case FORWARD: position_ += front_ * velocity; break;
      case BACKWARD: position_ -= front_ * velocity; break;
      case RIGHT: position_ += right_ * velocity; break;
      case LEFT: position_ -= right_ * velocity; break;
    }
  }

  void ProcessMouseMovement(Float x_offset, Float y_offset, GLboolean constrain_pitch = true) {
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
  void ProcessMouseScroll(Float y_offset) {
    if (zoom >= 1.0f && zoom <= 45.0f) zoom -= y_offset;
    if (zoom <= 1.0f) zoom = 1.0f;
    if (zoom >= 45.0f) zoom = 45.0f;
  }

  Float zoom;
 private:
  void UpdateCameraVectors() {
    // Calculate the new Front vector
    Vector3f front;
    front.x() = cos(math::radians(yaw_)) * cos(math::radians(pitch_));
    front.y() = sin(math::radians(pitch_));
    front.z() = sin(math::radians(yaw_)) * cos(math::radians(pitch_));
    front_ = front.normalized();
    // Also re-calculate the Right and Up vector
    right_ = front_.cross(worldup_).normalized();
    up_ = right_.cross(front_).normalized();
  }

  Vector3 position_, front_, up_, right_, worldup_;
  Float yaw_, pitch_;
  Float speed_, mouse_sensitivity_;
};

}
MIN_NAMESPACE_END

