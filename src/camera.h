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
#pragma once

#include "common.h"
#include "time_step.h"

namespace min::engine {

enum Direction {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
};

class Camera {
 public:
  Camera(float aspect,
         Vector3f pos = Vector3f(0.0f, 0.0f, 0.0f),
         Vector3f up = Vector3f(0.0f, 1.0f, 0.0f),
         float yaw = -90.0f, float pitch = 0.0f);

  inline Matrix4f GetViewMatrix() { return nf::math::LookAt(position_, position_ + direction_, vector_up_); }
  inline Matrix4f GetProjectionMatrix() { return nf::math::Perspective(nf::math::radians(fov_), aspect, z_near_, z_far_); }
  void ProcessKeyboard(Direction direction, TimeStep ts);
  void ProcessMouseMovement(float x_offset, float y_offset, GLboolean constrain_pitch = true);
  void ProcessMouseScroll(float y_offset);
  float aspect;
 private:
  void UpdateCameraVectors();
  Vector3f position_, direction_, vector_up_, right_, world_up_;
  float fov_;
  float yaw_, pitch_;
  float speed_, mouse_sensitivity_;
  float z_near_ = 0.1f, z_far_ = 100.0f;
};

}
