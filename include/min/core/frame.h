/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef MIN_INCLUDE_MIN_CORE_FRAME_H_
#define MIN_INCLUDE_MIN_CORE_FRAME_H_

#include <min/min.h>

MIN_NAMESPACE_BEGIN

class Frame {
 public:

  Vector3 ToLocal(const Vector3 &v) const {
    return Vector3(v.dot(s), v.dot(t), v.dot(n));
  }

  Vector3 ToWorld(const Vector3 &v) const {
    return s * v.x() + t * v.y() + n * v.z();
  }

  Vector3 s;
  Vector3 t;
  Vector3 n;
};
MIN_NAMESPACE_END

#endif //MIN_INCLUDE_MIN_CORE_FRAME_H_
