/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef CHIHAYA_SRC_CORE_VECTOR3_H_
#define CHIHAYA_SRC_CORE_VECTOR3_H_

#include "common.h"

CHIHAYA_NAMESPACE_BEGIN

template<typename T>
class Vector3 {
 public:
  // Vector3 Public Methods
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
  Vector3() { x = y = z = 0; }
  Vector3(T x, T y, T z) : x(x), y(y), z(z) { DCHECK(!HasNaNs()); }
  bool HasNaNs() const { return isNaN(x) || isNaN(y) || isNaN(z); }
#ifndef NDEBUG
  // The default versions of these are fine for release builds; for debug
  // we define them so that we can add the Assert checks.
  Vector3(const Vector3<T> &v) {
    DCHECK(!v.HasNaNs());
    x = v.x;
    y = v.y;
    z = v.z;
  }

  Vector3<T> &operator=(const Vector3<T> &v) {
    DCHECK(!v.HasNaNs());
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
  }
#endif  // !NDEBUG
  Vector3<T> operator+(const Vector3<T> &v) const {
    DCHECK(!v.HasNaNs());
    return Vector3(x + v.x, y + v.y, z + v.z);
  }
  Vector3<T> &operator+=(const Vector3<T> &v) {
    DCHECK(!v.HasNaNs());
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }
  Vector3<T> operator-(const Vector3<T> &v) const {
    DCHECK(!v.HasNaNs());
    return Vector3(x - v.x, y - v.y, z - v.z);
  }
  Vector3<T> &operator-=(const Vector3<T> &v) {
    DCHECK(!v.HasNaNs());
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }
  bool operator==(const Vector3<T> &v) const {
    return x == v.x && y == v.y && z == v.z;
  }
  bool operator!=(const Vector3<T> &v) const {
    return x != v.x || y != v.y || z != v.z;
  }
  template<typename U>
  Vector3<T> operator*(U s) const {
    return Vector3<T>(s * x, s * y, s * z);
  }
  template<typename U>
  Vector3<T> &operator*=(U s) {
    DCHECK(!isNaN(s));
    x *= s;
    y *= s;
    z *= s;
    return *this;
  }
  template<typename U>
  Vector3<T> operator/(U f) const {
    CHECK_NE(f, 0);
    Float inv = (Float) 1 / f;
    return Vector3<T>(x * inv, y * inv, z * inv);
  }

  template<typename U>
  Vector3<T> &operator/=(U f) {
    CHECK_NE(f, 0);
    Float inv = (Float) 1 / f;
    x *= inv;
    y *= inv;
    z *= inv;
    return *this;
  }
  Vector3<T> operator-() const { return Vector3<T>(-x, -y, -z); }
  Float LengthSquared() const { return x * x + y * y + z * z; }
  Float Length() const { return std::sqrt(LengthSquared()); }

  // Vector3 Public Data
  T x, y, z;
};

template<typename T>
inline std::ostream &operator<<(std::ostream &os, const Vector3<T> &v) {
  os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
  return os;
}

template<>
inline std::ostream &operator<<(std::ostream &os, const Vector3<Float> &v) {
  os << fmt::format("[ {}, {}, {} ]", v.x, v.y, v.z);
  return os;
}

typedef Vector3<Float> Vector3f;
typedef Vector3<int> Vector3i;

// Inline functions
template <typename T>
inline Vector3<T> Normalize(const Vector3<T> &v) {
  return v / v.Length();
}

CHIHAYA_NAMESPACE_END

#endif //CHIHAYA_SRC_CORE_VECTOR3_H_
