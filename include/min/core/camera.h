/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef MIN_INCLUDE_MIN_CORE_CAMERA_H_
#define MIN_INCLUDE_MIN_CORE_CAMERA_H_

#include <min/min.h>

MIN_NAMESPACE_BEGIN

struct CameraSample {
  Vector2f pFilm;
  Vector2f pLens;
  real time;
};

class Camera {
 public:
  virtual ~Camera();
  virtual real GenerateRay(const CameraSample &sample, Ray *ray) const = 0;
};

MIN_NAMESPACE_END

#endif //MIN_INCLUDE_MIN_CORE_CAMERA_H_
