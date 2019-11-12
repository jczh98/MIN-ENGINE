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

class Camera {
 public:
  void SetPosition(const Vector3f& pos) { position_ = pos; RecalculateViewMatrix(); }
  void SetDirection(const Vector3f& dir) { front_ = dir; RecalculateViewMatrix(); }
  void SetVectorUp(const Vector3f& up) { vector_up_ = up; RecalculateViewMatrix(); }
  void SetRotation(float rot) { rotation = rot; RecalculateViewMatrix(); }

  Matrix4f projection;
  Matrix4f view;
  Matrix4f view_projection;
 protected:
  Vector3f position_ = {0.0f, 0.0f, 0.0f};
  Vector3f front_ = {0.0f, 0.0f, -1.0f};
  Vector3f vector_up_ = {0.0f, 1.0f, 0.0f};
  float rotation;
 private:
  virtual void RecalculateViewMatrix() = 0;
};

class PerspectiveCamera : public Camera {
 public:
  PerspectiveCamera(float fov, float width, float height, float z_near, float z_far);
 private:
  virtual void RecalculateViewMatrix() override ;
};


}
