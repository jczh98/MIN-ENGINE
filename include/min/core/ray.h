/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef MIN_INCLUDE_MIN_CORE_RAY_H_
#define MIN_INCLUDE_MIN_CORE_RAY_H_

#include <min/min.h>

MIN_NAMESPACE_BEGIN

class Ray {
 public:
  Ray(): tMax(std::numeric_limits<Float>::infinity()), time(0.f) {}
  Ray(Vector3 &o, Vector3 &d, Float tMax = std::numeric_limits<Float>::infinity(),
      Float time = 0.f) : o(o), d(d), tMax(tMax), time(time) {}

  Vector3 operator()(Float t) const { return o + d * t;}

  Vector3 o, d;
  mutable Float tMax;
  Float time;
};

MIN_NAMESPACE_END

#endif //MIN_INCLUDE_MIN_CORE_RAY_H_
