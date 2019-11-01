/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include <min/engine/core/core.h>

namespace min::engine {

class Camera {
 public:
  Camera(float left, float right, float bottom, float top);
  void SetProjection(float left, float right, float bottom, float top);
  void SetPosition(const Vector3f& pos) { position = pos; RecalculateViewMatrix(); }
  void SetRotation(float rot) { rotation = rot; RecalculateViewMatrix(); }

  Matrix4f projection;
  Matrix4f view;
  Matrix4f view_projection;
  Vector3f position = {0.0f, 0.0f, 0.0f};
  float rotation;
 private:
  void RecalculateViewMatrix();
};


}

