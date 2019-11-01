/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#include <min/engine/renderer/camera.h>

namespace min::engine {

Camera::Camera(float left, float right, float bottom, float top) : view(Matrix4f::Identity()){
  projection = min::math::Ortho(left, right, bottom, top, -1.0f, 1.0f);
  view_projection = projection * view;
}
void Camera::SetProjection(float left, float right, float bottom, float top) {
  projection = min::math::Ortho(left, right, bottom, top, -1.0f, 1.0f);
  view_projection = projection * view;
}
void Camera::RecalculateViewMatrix() {
  Eigen::Affine3f transform = Eigen::Affine3f::Identity();
  transform.translate(position);
  Eigen::AngleAxisf rot = Eigen::AngleAxisf(min::math::radians(rotation), Vector3f(0, 0, 1));
  auto mat = transform * rot;
  view = mat.matrix().inverse();
  view_projection = projection * view;
}

}
