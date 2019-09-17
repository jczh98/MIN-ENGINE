/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef MIN_INCLUDE_MIN_CORE_ACCEL_H_
#define MIN_INCLUDE_MIN_CORE_ACCEL_H_

#include <min/min.h>
#include "box.h"
#include "ray.h"

MIN_NAMESPACE_BEGIN

// Acceleration data structure for ray intersection queries
class Accelerator {
 public:
  virtual void Build() = 0;
  virtual const Bounds3f &GetBoundingBox() const = 0;
  // Intersect a ray against all triangles stored in the scene and
  // return detailed intersection information.
  virtual bool Intersect(const Ray &r, Intersection &it) const = 0;


};
MIN_NAMESPACE_END
#endif //MIN_INCLUDE_MIN_CORE_ACCEL_H_
