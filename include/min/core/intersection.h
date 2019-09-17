/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef MIN_INCLUDE_MIN_CORE_INTERSECTION_H_
#define MIN_INCLUDE_MIN_CORE_INTERSECTION_H_

#include <min/min.h>

MIN_NAMESPACE_BEGIN

class Intersection {
 public:
  // Position of the surface intersection
  Vector3f p;
  // Unoccluded distance along the ray
  real t;
  // UV coordinates
  Vector2f uv;

};
MIN_NAMESPACE_END

#endif //MIN_INCLUDE_MIN_CORE_INTERSECTION_H_
