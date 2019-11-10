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

namespace min::engine {

enum Direction {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
};

class Camera {
 public:
  Camera(const Vector3f &position = Vector3f(0.0f, 0.0f, 0.0f),
         const Vector3f &up = Vector3f(0.0f, 1.0f, 0.0f),
         float yaw = -90.0f,
         float pitch = 0.0f);
  void ProcessKeyboard(Direction direction, float delta_time);
  void ProcessMouseMovement(float x_offset, float y_offset, GLboolean constrain_pitch = true);
  void ProcessMouseScroll(float y_offset);
  Matrix4f GetViewMatrix() { return nf::math::LookAt(position_, position_ + front_, up_);}
  float GetFOV() const { return zoom_; }
 private:
  void UpdateCamera();
  Vector3f position_, front_, up_, right_, world_up_;
  float yaw_, pitch_;
  float movement_speed_, mouse_sensitivity_, zoom_; // zoom_ also called fov
};

}
