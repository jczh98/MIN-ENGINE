/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef MIN_INCLUDE_MIN_CORE_AABB_H_
#define MIN_INCLUDE_MIN_CORE_AABB_H_

#include <min/min.h>

#include <utility>

MIN_NAMESPACE_BEGIN

class BoundingBox {

  BoundingBox(Vector3 lower, Vector3 upper)
      : lower_boundary(std::move(lower)), upper_boundary(std::move(upper)) {}

  Vector3 Center() const {
    return (lower_boundary + upper_boundary)*(Float) 0.5f;
  }
 public:
  Vector3 lower_boundary;
  Vector3 upper_boundary;
};
MIN_NAMESPACE_END

#endif //MIN_INCLUDE_MIN_CORE_AABB_H_
