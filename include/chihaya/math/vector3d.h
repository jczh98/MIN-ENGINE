/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef CHIHAYA_INCLUDE_CHIHAYA_MATH_VECTOR3D_H_
#define CHIHAYA_INCLUDE_CHIHAYA_MATH_VECTOR3D_H_

#include "vector.h"

CHIHAYA_NAMESPACE_BEGIN

template<typename T>
class VectorND<3, T> {
 public:
  // Vector3 Public Methods
  template<typename S>
  using Vector3D = VectorND<3, S>;

  T operator[](int i) const {
    DCHECK(i >= 0 && i <= 2);
    if (i == 0) return x;
    if (i == 1) return y;
    return z;
  }
  T &operator[](int i) {
    DCHECK(i >= 0 && i <= 2);
    if (i == 0) return x;
    if (i == 1) return y;
    return z;
  }
  VectorND() { x = y = z = 0; }
  VectorND(T x, T y, T z) : x(x), y(y), z(z) { DCHECK(!HasNaNs()); }
  bool HasNaNs() const { return isNaN(x) || isNaN(y) || isNaN(z); }
#ifndef NDEBUG
  VectorND(const Vector3D<T> &v) {
    DCHECK(!v.HasNaNs());
    x = v.x;
    y = v.y;
    z = v.z;
  }
  Vector3D<T> &operator=(const Vector3D<T> &v) {
    DCHECK(!v.HasNaNs());
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
  }
#endif // !NDEBUG
  Vector3D<T> operator+(const Vector3D<T> &v) const {
    DCHECK(!v.HasNaNs());
    return VectorND(x + v.x, y + v.y, z + v.z);
  }

  Vector3D<T> &operator+=(const Vector3D<T> &v) {
    DCHECK(!v.HasNaNs());
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }

  Vector3D<T> &operator*(const Vector3D<T> &v) const {
    DCHECK(!v.HasNaNs());
    return VectorND(x * v.x, y * v.y, z * v.z);
  }

  Vector3D<T> operator-(const Vector3D<T> &v) const {
    DCHECK(!v.HasNaNs());
    return VectorND(x - v.x, y - v.y, z - v.z);
  }

  Vector3D<T> &operator-=(const Vector3D<T> &v) {
    DCHECK(!v.HasNaNs());
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }

  bool operator==(const Vector3D<T> &v) const {
    return x == v.x && y == v.y && z == v.z;
  }

  bool operator!=(const Vector3D<T> &v) const {
    return x != v.x || y != v.y || z != v.z;
  }

  template <typename U>
  Vector3D<T> operator*(U s) const {
    return Vector3D<T>(s * x, s * y, s * z);
  }

  template <typename U>
  Vector3D<T> &operator*=(U s) const {
    DCHECK(!isNaN(s));
    x *= s;
    y *= s;
    z *= s;
    return *this;
  }

  template <typename U>
  Vector3D<T> operator/(U f) const {
    CHECK_NE(f, 0);
    real inv = (real) 1 / f;
    return VectorND(x * inv, y * inv, z * inv);
  }

  template <typename U>
  Vector3D<T> &operator/=(U f) {
    CHECK_NE(f, 0);
    real inv = (real) 1 / f;
    x *= inv;
    y *= inv;
    z *= inv;
    return *this;
  }

  Vector3D<T> operator-() const {
    return VectorND(-x, -y, -z);
  }

  real LengthSquared() const {
    return x * x + y * y + z * z;
  }

  real Length() const {
    return std::sqrt(LengthSquared());
  }

  // Vector3 Public Data
  T x, y, z;
};

template <typename T>
using Vector3D = VectorND<3, T>

template <typename T, typename U>
FORCE_INLINE Vector3D<T> operator*(U s, const Vector3D<T> &v) {
  return v * s;
}

template <typename T>
FORCE_INLINE Vector3D<T> Normalize(const Vector3D<T> &v) {
  return v / v.Length();
}

template <typename T>
FORCE_INLINE Vector3D<T> Abs(const Vector3D<T> &v) {
  return VectorND(std::abs(v.x), std::abs(v.y), std::abs(v.z));
}

template <typename T>
FORCE_INLINE T Dot(const Vector3D<T> &v1, const Vector3<T> &v2) {
  DCHECK(!v1.HasNaNs() && !v2.HasNaNs());
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template <typename T>
FORCE_INLINE T AbsDot(const Vector3D<T> &v1, const Vector3D<T> &v2) {
  return std::abs(Dot(v1, v2));
}

template <typename T>
FORCE_INLINE Vector3D<T> Cross(const Vector3D<T> &v1, const Vector3D<T> &v2) {
  DCHECK(!v1.HasNaNs() && !v2.HasNaNs());
  real v1x = v1.x, v1y = v1.y, v1z = v1.z;
  real v2x = v2.x, v2y = v2.y, v2z = v2.z;
  return VectorND((v1y * v2z) - (v1z * v2y),
                  (v1z * v2x) - (v1x * v2z),
                  (v1x * v2y) - (v1y * v2x));
}

CHIHAYA_NAMESPACE_END

#endif //CHIHAYA_INCLUDE_CHIHAYA_MATH_VECTOR3D_H_
