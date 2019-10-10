/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef MIN_INCLUDE_MIN_CORE_CAMERA_H_
#define MIN_INCLUDE_MIN_CORE_CAMERA_H_

#include <min/min.h>
#include "ray.h"
#include "filter.h"
#include "color.h"

MIN_NAMESPACE_BEGIN

struct CameraSample {
  Vector2f pFilm;
  Vector2f pLens;
  Float time;
};

class Camera {
 public:
  virtual Color3f SampleRay(Ray &ray,
      const Vector2 &sample_position,
      const Vector2 &aperture_sample) const = 0;
  Vector2i& output_size;
  std::shared_ptr<Filter> filter;
};

MIN_NAMESPACE_END

#endif //MIN_INCLUDE_MIN_CORE_CAMERA_H_
