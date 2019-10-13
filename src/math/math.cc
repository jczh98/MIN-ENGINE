/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#include <min/math/math.h>

MIN_NAMESPACE_BEGIN

namespace math {

Float radians(Float deg) {
  return deg*(pi/180.0f);
}

Matrix4 Perspective(Float fovy, Float aspect, Float z_near, Float z_far) {
  const Float tan_half_fovy = std::tan(fovy/2);
  Matrix4 ret = Matrix4f::Zero();
  ret(0, 0) = 1.0/(aspect*tan_half_fovy);
  ret(1, 1) = 1.0/(tan_half_fovy);
  ret(2, 2) = -(z_far + z_near)/(z_far - z_near);
  ret(3, 2) = -1.0;
  ret(2, 3) = -(2*z_far*z_near)/(z_far - z_near);
  return ret;
}

Matrix4 LookAt(const Vector3 &eye, const Vector3 &center, const Vector3 &up) {
  Vector3 f = (center - eye).normalized();
  Vector3 u = up.normalized();
  Vector3 s = f.cross(u).normalized();
  u = s.cross(f);

  Matrix4 res;
  res << s.x(), s.y(), s.z(), -s.dot(eye),
      u.x(), u.y(), u.z(), -u.dot(eye),
      -f.x(), -f.y(), -f.z(), f.dot(eye),
      0, 0, 0, 1;

  return res;
}

Matrix4 Ortho(const Float left, const Float right, const Float bottom, const Float top, const Float zNear, const Float zFar) {
  Matrix4 mat = Matrix4f::Identity();
  mat(0, 0) = 2.0 / (right - left);
  mat(1, 1) = 2.0 / (top - bottom);
  mat(2, 2) = -2.0 / (zFar - zNear);
  mat(3,0) = - (right + left) / (right - left);
  mat(3,1) = - (top + bottom) / (top - bottom);
  mat(3,2) = - (zFar + zNear) / (zFar - zNear);
  return mat;
}

}

MIN_NAMESPACE_END