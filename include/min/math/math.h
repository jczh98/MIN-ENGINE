/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef MIN_INCLUDE_MIN_MATH_MATH_H_
#define MIN_INCLUDE_MIN_MATH_MATH_H_

#include <min/common/util.h>
#include "linalg.h"

MIN_NAMESPACE_BEGIN

namespace math {

Float radians(Float deg) {
  return deg*(pi/180.0f);
}

Matrix4 Perspective(Float fovy, Float aspect, Float z_near, Float z_far) {
  const Float tan_half_fovy = std::tan(fovy/2);
  Matrix4 ret = Matrix4f::Identity();
  ret(0, 0) = 1/(aspect*tan_half_fovy);
  ret(1, 1) = 1/(tan_half_fovy);
  ret(2, 2) = -(z_far + z_near)/(z_far - z_near);
  ret(3, 2) = -1.0;
  ret(2, 3) = -(2*z_far*z_near)/(z_far - z_near);
  return ret;
}

Matrix4 LookAt(const Vector3 &position, const Vector3 &target, const Vector3 &up) {
  Vector3 f(target - position);
  Vector3 s(f.cross(up));
  Vector3 u(s.cross(f));
  f.normalize();
  s.normalize();
  u.normalize();
  Matrix4 res = Eigen::Matrix4f::Identity();
  res(0, 0) = s.x();
  res(0, 1) = s.y();
  res(0, 2) = s.z();
  res(1, 0) = u.x();
  res(1, 1) = u.y();
  res(1, 2) = u.z();
  res(2, 0) = -f.x();
  res(2, 1) = -f.y();
  res(2, 2) = -f.z();
  res(0, 3) = -s.dot(position);
  res(1, 3) = -u.dot(position);
  res(2, 3) = f.dot(position);
  return res;
}

}

MIN_NAMESPACE_END

#endif //MIN_INCLUDE_MIN_MATH_MATH_H_
