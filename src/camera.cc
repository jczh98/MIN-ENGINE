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

Camera::Camera(float left, float right, float bottom, float top) : view(Matrix4f::Identity()){
  projection = nf::math::Ortho(left, right, bottom, top, -1.0f, 1.0f);
  view_projection = projection * view;
}
void Camera::SetProjection(float left, float right, float bottom, float top) {
  projection = nf::math::Ortho(left, right, bottom, top, -1.0f, 1.0f);
  view_projection = projection * view;
}
void Camera::RecalculateViewMatrix() {
  Eigen::Affine3f transform = Eigen::Affine3f::Identity();
  transform.translate(position);
  Eigen::AngleAxisf rot = Eigen::AngleAxisf(nf::math::radians(rotation), Vector3f(0, 0, 1));
  auto mat = transform * rot;
  view = mat.matrix().inverse();
  view_projection = projection * view;
}

}
