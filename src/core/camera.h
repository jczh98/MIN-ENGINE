/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef CHIHAYA_SRC_CORE_CAMERA_H_
#define CHIHAYA_SRC_CORE_CAMERA_H_

#include "common.h"
#include "ray.h"

CHIHAYA_NAMESPACE_BEGIN

class Camera {
 public:

  Camera() {
    lower_left_corner = Vector3f(-2.0, -1.0, -1.0);
    horizontal = Vector3f(4.0, 0.0, 0.0);
    vertical = Vector3f(0, 2, 0);
    origin = Vector3f(0, 0, 0);
  }

  Ray GetRay(Float u, Float v) {
    return Ray(origin, lower_left_corner + horizontal * u + vertical * v - origin);
  }

  Vector3f origin;
  Vector3f lower_left_corner;
  Vector3f horizontal;
  Vector3f vertical;
};

CHIHAYA_NAMESPACE_END

#endif //CHIHAYA_SRC_CORE_CAMERA_H_
