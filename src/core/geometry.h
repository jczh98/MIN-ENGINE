/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef CHIHAYA_SRC_CORE_GEOMETRY_H_
#define CHIHAYA_SRC_CORE_GEOMETRY_H_

#include "globals.h"

namespace chihaya {

template<typename T>
inline bool isNaN(const T x) {
  return std::isnan(x);
}
template<>
inline bool isNaN(const int x) {
  return false;
}

// Vector Declarations
template<typename T>
class Vector2 {
 public:
  // Vector2 Public Methods
  Vector2() { x = y = 0; }
  Vector2(T xx, T yy) : x(xx), y(yy) { DCHECK(!HasNaNs()); }
  bool HasNaNs() const { return isNaN(x) || isNaN(y); }
  explicit Vector2(const Point2<T> &p);
  explicit Vector2(const Point3<T> &p);
#ifndef NDEBUG
  // The default versions of these are fine for release builds; for debug
  // we define them so that we can add the Assert checks.
  Vector2(const Vector2<T> &v) {
    DCHECK(!v.HasNaNs());
    x = v.x;
    y = v.y;
  }
  Vector2<T> &operator=(const Vector2<T> &v) {
    DCHECK(!v.HasNaNs());
    x = v.x;
    y = v.y;
    return *this;
  }
#endif  // !NDEBUG

  Vector2<T> operator+(const Vector2<T> &v) const {
    DCHECK(!v.HasNaNs());
    return Vector2(x + v.x, y + v.y);
  }

  Vector2<T> &operator+=(const Vector2<T> &v) {
    DCHECK(!v.HasNaNs());
    x += v.x;
    y += v.y;
    return *this;
  }
  Vector2<T> operator-(const Vector2<T> &v) const {
    DCHECK(!v.HasNaNs());
    return Vector2(x - v.x, y - v.y);
  }

  Vector2<T> &operator-=(const Vector2<T> &v) {
    DCHECK(!v.HasNaNs());
    x -= v.x;
    y -= v.y;
    return *this;
  }
  bool operator==(const Vector2<T> &v) const { return x == v.x && y == v.y; }
  bool operator!=(const Vector2<T> &v) const { return x != v.x || y != v.y; }
  template<typename U>
  Vector2<T> operator*(U f) const {
    return Vector2<T>(f * x, f * y);
  }

  template<typename U>
  Vector2<T> &operator*=(U f) {
    DCHECK(!isNaN(f));
    x *= f;
    y *= f;
    return *this;
  }
  template<typename U>
  Vector2<T> operator/(U f) const {
    CHECK_NE(f, 0);
    Float inv = (Float) 1 / f;
    return Vector2<T>(x * inv, y * inv);
  }

  template<typename U>
  Vector2<T> &operator/=(U f) {
    CHECK_NE(f, 0);
    Float inv = (Float) 1 / f;
    x *= inv;
    y *= inv;
    return *this;
  }
  Vector2<T> operator-() const { return Vector2<T>(-x, -y); }
  T operator[](int i) const {
    DCHECK(i >= 0 && i <= 1);
    if (i == 0) return x;
    return y;
  }

  T &operator[](int i) {
    DCHECK(i >= 0 && i <= 1);
    if (i == 0) return x;
    return y;
  }
  Float LengthSquared() const { return x * x + y * y; }
  Float Length() const { return std::sqrt(LengthSquared()); }

  // Vector2 Public Data
  T x, y;
};

template<typename T>
inline std::ostream &operator<<(std::ostream &os, const Vector2<T> &v) {
  os << "[ " << v.x << ", " << v.y << " ]";
  return os;
}

template<>
inline std::ostream &operator<<(std::ostream &os, const Vector2<Float> &v) {
  // TODO
  // os << StringPrintf("[ %f, %f ]", v.x, v.y);
  return os;
}

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
  explicit Vector3(const Point3<T> &p);
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
  explicit Vector3(const Normal3<T> &n);

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
  // TODO
  //os << StringPrintf("[ %f, %f, %f ]", v.x, v.y, v.z);
  return os;
}

typedef Vector2<Float> Vector2f;
typedef Vector2<int> Vector2i;
typedef Vector3<Float> Vector3f;
typedef Vector3<int> Vector3i;

// Point Declarations
template<typename T>
class Point2 {
 public:
  // Point2 Public Methods
  explicit Point2(const Point3<T> &p) : x(p.x), y(p.y) { DCHECK(!HasNaNs()); }
  Point2() { x = y = 0; }
  Point2(T xx, T yy) : x(xx), y(yy) { DCHECK(!HasNaNs()); }

  template<typename U>
  explicit Point2(const Point2<U> &p) {
    x = (T) p.x;
    y = (T) p.y;
    DCHECK(!HasNaNs());
  }

  template<typename U>
  explicit Point2(const Vector2<U> &p) {
    x = (T) p.x;
    y = (T) p.y;
    DCHECK(!HasNaNs());
  }

  template<typename U>
  explicit operator Vector2<U>() const {
    return Vector2<U>(x, y);
  }

#ifndef NDEBUG
  Point2(const Point2<T> &p) {
    DCHECK(!p.HasNaNs());
    x = p.x;
    y = p.y;
  }

  Point2<T> &operator=(const Point2<T> &p) {
    DCHECK(!p.HasNaNs());
    x = p.x;
    y = p.y;
    return *this;
  }
#endif  // !NDEBUG
  Point2<T> operator+(const Vector2<T> &v) const {
    DCHECK(!v.HasNaNs());
    return Point2<T>(x + v.x, y + v.y);
  }

  Point2<T> &operator+=(const Vector2<T> &v) {
    DCHECK(!v.HasNaNs());
    x += v.x;
    y += v.y;
    return *this;
  }
  Vector2<T> operator-(const Point2<T> &p) const {
    DCHECK(!p.HasNaNs());
    return Vector2<T>(x - p.x, y - p.y);
  }

  Point2<T> operator-(const Vector2<T> &v) const {
    DCHECK(!v.HasNaNs());
    return Point2<T>(x - v.x, y - v.y);
  }
  Point2<T> operator-() const { return Point2<T>(-x, -y); }
  Point2<T> &operator-=(const Vector2<T> &v) {
    DCHECK(!v.HasNaNs());
    x -= v.x;
    y -= v.y;
    return *this;
  }
  Point2<T> &operator+=(const Point2<T> &p) {
    DCHECK(!p.HasNaNs());
    x += p.x;
    y += p.y;
    return *this;
  }
  Point2<T> operator+(const Point2<T> &p) const {
    DCHECK(!p.HasNaNs());
    return Point2<T>(x + p.x, y + p.y);
  }
  template<typename U>
  Point2<T> operator*(U f) const {
    return Point2<T>(f * x, f * y);
  }
  template<typename U>
  Point2<T> &operator*=(U f) {
    x *= f;
    y *= f;
    return *this;
  }
  template<typename U>
  Point2<T> operator/(U f) const {
    CHECK_NE(f, 0);
    Float inv = (Float) 1 / f;
    return Point2<T>(inv * x, inv * y);
  }
  template<typename U>
  Point2<T> &operator/=(U f) {
    CHECK_NE(f, 0);
    Float inv = (Float) 1 / f;
    x *= inv;
    y *= inv;
    return *this;
  }
  T operator[](int i) const {
    DCHECK(i >= 0 && i <= 1);
    if (i == 0) return x;
    return y;
  }

  T &operator[](int i) {
    DCHECK(i >= 0 && i <= 1);
    if (i == 0) return x;
    return y;
  }
  bool operator==(const Point2<T> &p) const { return x == p.x && y == p.y; }
  bool operator!=(const Point2<T> &p) const { return x != p.x || y != p.y; }
  bool HasNaNs() const { return isNaN(x) || isNaN(y); }

  // Point2 Public Data
  T x, y;
};

template<typename T>
inline std::ostream &operator<<(std::ostream &os, const Point2<T> &v) {
  os << "[ " << v.x << ", " << v.y << " ]";
  return os;
}

template<>
inline std::ostream &operator<<(std::ostream &os, const Point2<Float> &v) {
  // TODO
  //os << StringPrintf("[ %f, %f ]", v.x, v.y);
  return os;
}

template<typename T>
class Point3 {
 public:
  // Point3 Public Methods
  Point3() { x = y = z = 0; }
  Point3(T x, T y, T z) : x(x), y(y), z(z) { DCHECK(!HasNaNs()); }
  template<typename U>
  explicit Point3(const Point3<U> &p)
      : x((T) p.x), y((T) p.y), z((T) p.z) {
    DCHECK(!HasNaNs());
  }
  template<typename U>
  explicit operator Vector3<U>() const {
    return Vector3<U>(x, y, z);
  }
#ifndef NDEBUG
  Point3(const Point3<T> &p) {
    DCHECK(!p.HasNaNs());
    x = p.x;
    y = p.y;
    z = p.z;
  }

  Point3<T> &operator=(const Point3<T> &p) {
    DCHECK(!p.HasNaNs());
    x = p.x;
    y = p.y;
    z = p.z;
    return *this;
  }
#endif  // !NDEBUG
  Point3<T> operator+(const Vector3<T> &v) const {
    DCHECK(!v.HasNaNs());
    return Point3<T>(x + v.x, y + v.y, z + v.z);
  }
  Point3<T> &operator+=(const Vector3<T> &v) {
    DCHECK(!v.HasNaNs());
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }
  Vector3<T> operator-(const Point3<T> &p) const {
    DCHECK(!p.HasNaNs());
    return Vector3<T>(x - p.x, y - p.y, z - p.z);
  }
  Point3<T> operator-(const Vector3<T> &v) const {
    DCHECK(!v.HasNaNs());
    return Point3<T>(x - v.x, y - v.y, z - v.z);
  }
  Point3<T> &operator-=(const Vector3<T> &v) {
    DCHECK(!v.HasNaNs());
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }
  Point3<T> &operator+=(const Point3<T> &p) {
    DCHECK(!p.HasNaNs());
    x += p.x;
    y += p.y;
    z += p.z;
    return *this;
  }
  Point3<T> operator+(const Point3<T> &p) const {
    DCHECK(!p.HasNaNs());
    return Point3<T>(x + p.x, y + p.y, z + p.z);
  }
  template<typename U>
  Point3<T> operator*(U f) const {
    return Point3<T>(f * x, f * y, f * z);
  }
  template<typename U>
  Point3<T> &operator*=(U f) {
    x *= f;
    y *= f;
    z *= f;
    return *this;
  }
  template<typename U>
  Point3<T> operator/(U f) const {
    CHECK_NE(f, 0);
    Float inv = (Float) 1 / f;
    return Point3<T>(inv * x, inv * y, inv * z);
  }
  template<typename U>
  Point3<T> &operator/=(U f) {
    CHECK_NE(f, 0);
    Float inv = (Float) 1 / f;
    x *= inv;
    y *= inv;
    z *= inv;
    return *this;
  }
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
  bool operator==(const Point3<T> &p) const {
    return x == p.x && y == p.y && z == p.z;
  }
  bool operator!=(const Point3<T> &p) const {
    return x != p.x || y != p.y || z != p.z;
  }
  bool HasNaNs() const { return isNaN(x) || isNaN(y) || isNaN(z); }
  Point3<T> operator-() const { return Point3<T>(-x, -y, -z); }

  // Point3 Public Data
  T x, y, z;
};

template<typename T>
inline std::ostream &operator<<(std::ostream &os, const Point3<T> &v) {
  os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
  return os;
}

template<>
inline std::ostream &operator<<(std::ostream &os, const Point3<Float> &v) {
  // TODO
  //os << StringPrintf("[ %f, %f, %f ]", v.x, v.y, v.z);
  return os;
}

typedef Point2<Float> Point2f;
typedef Point2<int> Point2i;
typedef Point3<Float> Point3f;
typedef Point3<int> Point3i;

// Normal Declarations
template<typename T>
class Normal3 {
 public:
  // Normal3 Public Methods
  Normal3() { x = y = z = 0; }
  Normal3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) { DCHECK(!HasNaNs()); }
  Normal3<T> operator-() const { return Normal3(-x, -y, -z); }
  Normal3<T> operator+(const Normal3<T> &n) const {
    DCHECK(!n.HasNaNs());
    return Normal3<T>(x + n.x, y + n.y, z + n.z);
  }

  Normal3<T> &operator+=(const Normal3<T> &n) {
    DCHECK(!n.HasNaNs());
    x += n.x;
    y += n.y;
    z += n.z;
    return *this;
  }
  Normal3<T> operator-(const Normal3<T> &n) const {
    DCHECK(!n.HasNaNs());
    return Normal3<T>(x - n.x, y - n.y, z - n.z);
  }

  Normal3<T> &operator-=(const Normal3<T> &n) {
    DCHECK(!n.HasNaNs());
    x -= n.x;
    y -= n.y;
    z -= n.z;
    return *this;
  }
  bool HasNaNs() const { return isNaN(x) || isNaN(y) || isNaN(z); }
  template<typename U>
  Normal3<T> operator*(U f) const {
    return Normal3<T>(f * x, f * y, f * z);
  }

  template<typename U>
  Normal3<T> &operator*=(U f) {
    x *= f;
    y *= f;
    z *= f;
    return *this;
  }
  template<typename U>
  Normal3<T> operator/(U f) const {
    CHECK_NE(f, 0);
    Float inv = (Float) 1 / f;
    return Normal3<T>(x * inv, y * inv, z * inv);
  }

  template<typename U>
  Normal3<T> &operator/=(U f) {
    CHECK_NE(f, 0);
    Float inv = (Float) 1 / f;
    x *= inv;
    y *= inv;
    z *= inv;
    return *this;
  }
  Float LengthSquared() const { return x * x + y * y + z * z; }
  Float Length() const { return std::sqrt(LengthSquared()); }

#ifndef NDEBUG
  Normal3<T>(const Normal3<T> &n) {
    DCHECK(!n.HasNaNs());
    x = n.x;
    y = n.y;
    z = n.z;
  }

  Normal3<T> &operator=(const Normal3<T> &n) {
    DCHECK(!n.HasNaNs());
    x = n.x;
    y = n.y;
    z = n.z;
    return *this;
  }
#endif  // !NDEBUG
  explicit Normal3<T>(const Vector3<T> &v) : x(v.x), y(v.y), z(v.z) {
    DCHECK(!v.HasNaNs());
  }
  bool operator==(const Normal3<T> &n) const {
    return x == n.x && y == n.y && z == n.z;
  }
  bool operator!=(const Normal3<T> &n) const {
    return x != n.x || y != n.y || z != n.z;
  }

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

  // Normal3 Public Data
  T x, y, z;
};

template<typename T>
inline std::ostream &operator<<(std::ostream &os, const Normal3<T> &v) {
  os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
  return os;
}

template<>
inline std::ostream &operator<<(std::ostream &os, const Normal3<Float> &v) {
  // TODO
  //os << StringPrintf("[ %f, %f, %f ]", v.x, v.y, v.z);
  return os;
}

typedef Normal3<Float> Normal3f;

// Bounds Declarations
template<typename T>
class Bounds2 {
 public:
  // Bounds2 Public Methods
  Bounds2() {
    T min_num = std::numeric_limits<T>::lowest();
    T max_num = std::numeric_limits<T>::max();
    p_min = Point2<T>(max_num, max_num);
    p_max = Point2<T>(min_num, min_num);
  }
  explicit Bounds2(const Point2<T> &p) : p_min(p), p_max(p) {}
  Bounds2(const Point2<T> &p1, const Point2<T> &p2) {
    p_min = Point2<T>(std::min(p1.x, p2.x), std::min(p1.y, p2.y));
    p_max = Point2<T>(std::max(p1.x, p2.x), std::max(p1.y, p2.y));
  }
  template<typename U>
  explicit operator Bounds2<U>() const {
    return Bounds2<U>((Point2<U>) p_min, (Point2<U>) p_max);
  }

  Vector2<T> Diagonal() const { return p_max - p_min; }
  T Area() const {
    Vector2<T> d = p_max - p_min;
    return (d.x * d.y);
  }
  int MaximumExtent() const {
    Vector2<T> diag = Diagonal();
    if (diag.x > diag.y)
      return 0;
    else
      return 1;
  }
  inline const Point2<T> &operator[](int i) const {
    DCHECK(i == 0 || i == 1);
    return (i == 0) ? p_min : p_max;
  }
  inline Point2<T> &operator[](int i) {
    DCHECK(i == 0 || i == 1);
    return (i == 0) ? p_min : p_max;
  }
  bool operator==(const Bounds2<T> &b) const {
    return b.p_min == p_min && b.p_max == p_max;
  }
  bool operator!=(const Bounds2<T> &b) const {
    return b.p_min != p_min || b.p_max != p_max;
  }
  Point2<T> Lerp(const Point2f &t) const {
    return Point2<T>(chihaya::Lerp(t.x, p_min.x, p_max.x),
                     chihaya::Lerp(t.y, p_min.y, p_max.y));
  }
  Vector2<T> Offset(const Point2<T> &p) const {
    Vector2<T> o = p - p_min;
    if (p_max.x > p_min.x) o.x /= p_max.x - p_min.x;
    if (p_max.y > p_min.y) o.y /= p_max.y - p_min.y;
    return o;
  }
  void BoundingSphere(Point2<T> *c, Float *rad) const {
    *c = (p_min + p_max) / 2;
    *rad = Inside(*c, *this) ? Distance(*c, p_max) : 0;
  }
  friend std::ostream &operator<<(std::ostream &os, const Bounds2<T> &b) {
    os << "[ " << b.p_min << " - " << b.p_max << " ]";
    return os;
  }

  // Bounds2 Public Data
  Point2<T> p_min, p_max;
};

template<typename T>
class Bounds3 {
 public:
  // Bounds3 Public Methods
  Bounds3() {
    T min_num = std::numeric_limits<T>::lowest();
    T max_num = std::numeric_limits<T>::max();
    p_min = Point3<T>(max_num, max_num, max_num);
    p_max = Point3<T>(min_num, min_num, min_num);
  }
  explicit Bounds3(const Point3<T> &p) : p_min(p), p_max(p) {}
  Bounds3(const Point3<T> &p1, const Point3<T> &p2)
      : p_min(std::min(p1.x, p2.x), std::min(p1.y, p2.y),
              std::min(p1.z, p2.z)),
        p_max(std::max(p1.x, p2.x), std::max(p1.y, p2.y),
              std::max(p1.z, p2.z)) {}
  const Point3<T> &operator[](int i) const;
  Point3<T> &operator[](int i);
  bool operator==(const Bounds3<T> &b) const {
    return b.p_min == p_min && b.p_max == p_max;
  }
  bool operator!=(const Bounds3<T> &b) const {
    return b.p_min != p_min || b.p_max != p_max;
  }
  Point3<T> Corner(int corner) const {
    DCHECK(corner >= 0 && corner < 8);
    return Point3<T>((*this)[(corner & 1)].x,
                     (*this)[(corner & 2) ? 1 : 0].y,
                     (*this)[(corner & 4) ? 1 : 0].z);
  }
  Vector3<T> Diagonal() const { return p_max - p_min; }
  T SurfaceArea() const {
    Vector3<T> d = Diagonal();
    return 2 * (d.x * d.y + d.x * d.z + d.y * d.z);
  }
  T Volume() const {
    Vector3<T> d = Diagonal();
    return d.x * d.y * d.z;
  }
  int MaximumExtent() const {
    Vector3<T> d = Diagonal();
    if (d.x > d.y && d.x > d.z)
      return 0;
    else if (d.y > d.z)
      return 1;
    else
      return 2;
  }
  Point3<T> Lerp(const Point3f &t) const {
    return Point3<T>(chihaya::Lerp(t.x, p_min.x, p_max.x),
                     chihaya::Lerp(t.y, p_min.y, p_max.y),
                     chihaya::Lerp(t.z, p_min.z, p_max.z));
  }
  Vector3<T> Offset(const Point3<T> &p) const {
    Vector3<T> o = p - p_min;
    if (p_max.x > p_min.x) o.x /= p_max.x - p_min.x;
    if (p_max.y > p_min.y) o.y /= p_max.y - p_min.y;
    if (p_max.z > p_min.z) o.z /= p_max.z - p_min.z;
    return o;
  }
  void BoundingSphere(Point3<T> *center, Float *radius) const {
    *center = (p_min + p_max) / 2;
    *radius = Inside(*center, *this) ? Distance(*center, p_max) : 0;
  }
  template<typename U>
  explicit operator Bounds3<U>() const {
    return Bounds3<U>((Point3<U>) p_min, (Point3<U>) p_max);
  }
  bool IntersectP(const Ray &ray, Float *hitt0 = nullptr,
                  Float *hitt1 = nullptr) const;
  inline bool IntersectP(const Ray &ray, const Vector3f &invDir,
                         const int dirIsNeg[3]) const;
  friend std::ostream &operator<<(std::ostream &os, const Bounds3<T> &b) {
    os << "[ " << b.p_min << " - " << b.p_max << " ]";
    return os;
  }

  // Bounds3 Public Data
  Point3<T> p_min, p_max;
};

typedef Bounds2<Float> Bounds2f;
typedef Bounds2<int> Bounds2i;
typedef Bounds3<Float> Bounds3f;
typedef Bounds3<int> Bounds3i;

class Bounds2iIterator : public std::forward_iterator_tag {
 public:
  Bounds2iIterator(const Bounds2i &b, const Point2i &pt)
      : p(pt), bounds(&b) {}
  Bounds2iIterator operator++() {
    advance();
    return *this;
  }
  Bounds2iIterator operator++(int) {
    Bounds2iIterator old = *this;
    advance();
    return old;
  }
  bool operator==(const Bounds2iIterator &bi) const {
    return p == bi.p && bounds == bi.bounds;
  }
  bool operator!=(const Bounds2iIterator &bi) const {
    return p != bi.p || bounds != bi.bounds;
  }

  Point2i operator*() const { return p; }

 private:
  void advance() {
    ++p.x;
    if (p.x == bounds->p_max.x) {
      p.x = bounds->p_min.x;
      ++p.y;
    }
  }
  Point2i p;
  const Bounds2i *bounds;
};

// Ray Declarations
class Ray {
 public:
  // Ray Public Methods
  Ray() : t_max(Infinity), time(0.f), medium(nullptr) {}
  Ray(const Point3f &o, const Vector3f &d, Float t_max = Infinity,
      Float time = 0.f, const Medium *medium = nullptr)
      : o(o), d(d), t_max(t_max), time(time), medium(medium) {}
  Point3f operator()(Float t) const { return o + d * t; }
  bool HasNaNs() const { return (o.HasNaNs() || d.HasNaNs() || isNaN(t_max)); }
  friend std::ostream &operator<<(std::ostream &os, const Ray &r) {
    os << "[o=" << r.o << ", d=" << r.d << ", t_max=" << r.t_max
       << ", time=" << r.time << "]";
    return os;
  }

  // Ray Public Data
  Point3f o;
  Vector3f d;
  mutable Float t_max;
  Float time;
  const Medium *medium;
};

class RayDifferential : public Ray {
 public:
  // RayDifferential Public Methods
  RayDifferential() { has_differentials = false; }
  RayDifferential(const Point3f &o, const Vector3f &d, Float t_max = Infinity,
                  Float time = 0.f, const Medium *medium = nullptr)
      : Ray(o, d, t_max, time, medium) {
    has_differentials = false;
  }
  RayDifferential(const Ray &ray) : Ray(ray) { has_differentials = false; }
  bool HasNaNs() const {
    return Ray::HasNaNs() ||
        (has_differentials &&
            (rx_origin.HasNaNs() || ry_origin.HasNaNs() ||
                rx_direction.HasNaNs() || ry_direction.HasNaNs()));
  }
  void ScaleDifferentials(Float s) {
    rx_origin = o + (rx_origin - o) * s;
    ry_origin = o + (ry_origin - o) * s;
    rx_direction = d + (rx_direction - d) * s;
    ry_direction = d + (ry_direction - d) * s;
  }
  friend std::ostream &operator<<(std::ostream &os, const RayDifferential &r) {
    os << "[ " << (Ray &) r << " has differentials: " <<
       (r.has_differentials ? "true" : "false") << ", xo = " << r.rx_origin <<
       ", xd = " << r.rx_direction << ", yo = " << r.ry_origin << ", yd = " <<
       r.ry_direction;
    return os;
  }

  // RayDifferential Public Data
  bool has_differentials;
  Point3f rx_origin, ry_origin;
  Vector3f rx_direction, ry_direction;
};

// Geometry Inline Functions
template<typename T>
inline Vector3<T>::Vector3(const Point3<T> &p)
    : x(p.x), y(p.y), z(p.z) {
  DCHECK(!HasNaNs());
}

template<typename T, typename U>
inline Vector3<T> operator*(U s, const Vector3<T> &v) {
  return v * s;
}
template<typename T>
Vector3<T> Abs(const Vector3<T> &v) {
  return Vector3<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z));
}

template<typename T>
inline T Dot(const Vector3<T> &v1, const Vector3<T> &v2) {
  DCHECK(!v1.HasNaNs() && !v2.HasNaNs());
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template<typename T>
inline T AbsDot(const Vector3<T> &v1, const Vector3<T> &v2) {
  DCHECK(!v1.HasNaNs() && !v2.HasNaNs());
  return std::abs(Dot(v1, v2));
}

template<typename T>
inline Vector3<T> Cross(const Vector3<T> &v1, const Vector3<T> &v2) {
  DCHECK(!v1.HasNaNs() && !v2.HasNaNs());
  double v1x = v1.x, v1y = v1.y, v1z = v1.z;
  double v2x = v2.x, v2y = v2.y, v2z = v2.z;
  return Vector3<T>((v1y * v2z) - (v1z * v2y), (v1z * v2x) - (v1x * v2z),
                    (v1x * v2y) - (v1y * v2x));
}

template<typename T>
inline Vector3<T> Cross(const Vector3<T> &v1, const Normal3<T> &v2) {
  DCHECK(!v1.HasNaNs() && !v2.HasNaNs());
  double v1x = v1.x, v1y = v1.y, v1z = v1.z;
  double v2x = v2.x, v2y = v2.y, v2z = v2.z;
  return Vector3<T>((v1y * v2z) - (v1z * v2y), (v1z * v2x) - (v1x * v2z),
                    (v1x * v2y) - (v1y * v2x));
}

template<typename T>
inline Vector3<T> Cross(const Normal3<T> &v1, const Vector3<T> &v2) {
  DCHECK(!v1.HasNaNs() && !v2.HasNaNs());
  double v1x = v1.x, v1y = v1.y, v1z = v1.z;
  double v2x = v2.x, v2y = v2.y, v2z = v2.z;
  return Vector3<T>((v1y * v2z) - (v1z * v2y), (v1z * v2x) - (v1x * v2z),
                    (v1x * v2y) - (v1y * v2x));
}

template<typename T>
inline Vector3<T> Normalize(const Vector3<T> &v) {
  return v / v.Length();
}
template<typename T>
T MinComponent(const Vector3<T> &v) {
  return std::min(v.x, std::min(v.y, v.z));
}

template<typename T>
T MaxComponent(const Vector3<T> &v) {
  return std::max(v.x, std::max(v.y, v.z));
}

template<typename T>
int MaxDimension(const Vector3<T> &v) {
  return (v.x > v.y) ? ((v.x > v.z) ? 0 : 2) : ((v.y > v.z) ? 1 : 2);
}

template<typename T>
Vector3<T> Min(const Vector3<T> &p1, const Vector3<T> &p2) {
  return Vector3<T>(std::min(p1.x, p2.x), std::min(p1.y, p2.y),
                    std::min(p1.z, p2.z));
}

template<typename T>
Vector3<T> Max(const Vector3<T> &p1, const Vector3<T> &p2) {
  return Vector3<T>(std::max(p1.x, p2.x), std::max(p1.y, p2.y),
                    std::max(p1.z, p2.z));
}

template<typename T>
Vector3<T> Permute(const Vector3<T> &v, int x, int y, int z) {
  return Vector3<T>(v[x], v[y], v[z]);
}

template<typename T>
inline void CoordinateSystem(const Vector3<T> &v1, Vector3<T> *v2,
                             Vector3<T> *v3) {
  if (std::abs(v1.x) > std::abs(v1.y))
    *v2 = Vector3<T>(-v1.z, 0, v1.x) / std::sqrt(v1.x * v1.x + v1.z * v1.z);
  else
    *v2 = Vector3<T>(0, v1.z, -v1.y) / std::sqrt(v1.y * v1.y + v1.z * v1.z);
  *v3 = Cross(v1, *v2);
}

template<typename T>
Vector2<T>::Vector2(const Point2<T> &p)
    : x(p.x), y(p.y) {
  DCHECK(!HasNaNs());
}

template<typename T>
Vector2<T>::Vector2(const Point3<T> &p)
    : x(p.x), y(p.y) {
  DCHECK(!HasNaNs());
}

template<typename T, typename U>
inline Vector2<T> operator*(U f, const Vector2<T> &v) {
  return v * f;
}
template<typename T>
inline Float Dot(const Vector2<T> &v1, const Vector2<T> &v2) {
  DCHECK(!v1.HasNaNs() && !v2.HasNaNs());
  return v1.x * v2.x + v1.y * v2.y;
}

template<typename T>
inline Float AbsDot(const Vector2<T> &v1, const Vector2<T> &v2) {
  DCHECK(!v1.HasNaNs() && !v2.HasNaNs());
  return std::abs(Dot(v1, v2));
}

template<typename T>
inline Vector2<T> Normalize(const Vector2<T> &v) {
  return v / v.Length();
}
template<typename T>
Vector2<T> Abs(const Vector2<T> &v) {
  return Vector2<T>(std::abs(v.x), std::abs(v.y));
}

template<typename T>
inline Float Distance(const Point3<T> &p1, const Point3<T> &p2) {
  return (p1 - p2).Length();
}

template<typename T>
inline Float DistanceSquared(const Point3<T> &p1, const Point3<T> &p2) {
  return (p1 - p2).LengthSquared();
}

template<typename T, typename U>
inline Point3<T> operator*(U f, const Point3<T> &p) {
  DCHECK(!p.HasNaNs());
  return p * f;
}

template<typename T>
Point3<T> Lerp(Float t, const Point3<T> &p0, const Point3<T> &p1) {
  return (1 - t) * p0 + t * p1;
}

template<typename T>
Point3<T> Min(const Point3<T> &p1, const Point3<T> &p2) {
  return Point3<T>(std::min(p1.x, p2.x), std::min(p1.y, p2.y),
                   std::min(p1.z, p2.z));
}

template<typename T>
Point3<T> Max(const Point3<T> &p1, const Point3<T> &p2) {
  return Point3<T>(std::max(p1.x, p2.x), std::max(p1.y, p2.y),
                   std::max(p1.z, p2.z));
}

template<typename T>
Point3<T> Floor(const Point3<T> &p) {
  return Point3<T>(std::floor(p.x), std::floor(p.y), std::floor(p.z));
}

template<typename T>
Point3<T> Ceil(const Point3<T> &p) {
  return Point3<T>(std::ceil(p.x), std::ceil(p.y), std::ceil(p.z));
}

template<typename T>
Point3<T> Abs(const Point3<T> &p) {
  return Point3<T>(std::abs(p.x), std::abs(p.y), std::abs(p.z));
}

template<typename T>
inline Float Distance(const Point2<T> &p1, const Point2<T> &p2) {
  return (p1 - p2).Length();
}

template<typename T>
inline Float DistanceSquared(const Point2<T> &p1, const Point2<T> &p2) {
  return (p1 - p2).LengthSquared();
}

template<typename T, typename U>
inline Point2<T> operator*(U f, const Point2<T> &p) {
  DCHECK(!p.HasNaNs());
  return p * f;
}

template<typename T>
Point2<T> Floor(const Point2<T> &p) {
  return Point2<T>(std::floor(p.x), std::floor(p.y));
}

template<typename T>
Point2<T> Ceil(const Point2<T> &p) {
  return Point2<T>(std::ceil(p.x), std::ceil(p.y));
}

template<typename T>
Point2<T> Lerp(Float t, const Point2<T> &v0, const Point2<T> &v1) {
  return (1 - t) * v0 + t * v1;
}

template<typename T>
Point2<T> Min(const Point2<T> &pa, const Point2<T> &pb) {
  return Point2<T>(std::min(pa.x, pb.x), std::min(pa.y, pb.y));
}

template<typename T>
Point2<T> Max(const Point2<T> &pa, const Point2<T> &pb) {
  return Point2<T>(std::max(pa.x, pb.x), std::max(pa.y, pb.y));
}

template<typename T>
Point3<T> Permute(const Point3<T> &p, int x, int y, int z) {
  return Point3<T>(p[x], p[y], p[z]);
}

template<typename T, typename U>
inline Normal3<T> operator*(U f, const Normal3<T> &n) {
  return Normal3<T>(f * n.x, f * n.y, f * n.z);
}

template<typename T>
inline Normal3<T> Normalize(const Normal3<T> &n) {
  return n / n.Length();
}

template<typename T>
inline Vector3<T>::Vector3(const Normal3<T> &n)
    : x(n.x), y(n.y), z(n.z) {
  DCHECK(!n.HasNaNs());
}

template<typename T>
inline T Dot(const Normal3<T> &n1, const Vector3<T> &v2) {
  DCHECK(!n1.HasNaNs() && !v2.HasNaNs());
  return n1.x * v2.x + n1.y * v2.y + n1.z * v2.z;
}

template<typename T>
inline T Dot(const Vector3<T> &v1, const Normal3<T> &n2) {
  DCHECK(!v1.HasNaNs() && !n2.HasNaNs());
  return v1.x * n2.x + v1.y * n2.y + v1.z * n2.z;
}

template<typename T>
inline T Dot(const Normal3<T> &n1, const Normal3<T> &n2) {
  DCHECK(!n1.HasNaNs() && !n2.HasNaNs());
  return n1.x * n2.x + n1.y * n2.y + n1.z * n2.z;
}

template<typename T>
inline T AbsDot(const Normal3<T> &n1, const Vector3<T> &v2) {
  DCHECK(!n1.HasNaNs() && !v2.HasNaNs());
  return std::abs(n1.x * v2.x + n1.y * v2.y + n1.z * v2.z);
}

template<typename T>
inline T AbsDot(const Vector3<T> &v1, const Normal3<T> &n2) {
  DCHECK(!v1.HasNaNs() && !n2.HasNaNs());
  return std::abs(v1.x * n2.x + v1.y * n2.y + v1.z * n2.z);
}

template<typename T>
inline T AbsDot(const Normal3<T> &n1, const Normal3<T> &n2) {
  DCHECK(!n1.HasNaNs() && !n2.HasNaNs());
  return std::abs(n1.x * n2.x + n1.y * n2.y + n1.z * n2.z);
}

template<typename T>
inline Normal3<T> Faceforward(const Normal3<T> &n, const Vector3<T> &v) {
  return (Dot(n, v) < 0.f) ? -n : n;
}

template<typename T>
inline Normal3<T> Faceforward(const Normal3<T> &n, const Normal3<T> &n2) {
  return (Dot(n, n2) < 0.f) ? -n : n;
}

template<typename T>
inline Vector3<T> Faceforward(const Vector3<T> &v, const Vector3<T> &v2) {
  return (Dot(v, v2) < 0.f) ? -v : v;
}

template<typename T>
inline Vector3<T> Faceforward(const Vector3<T> &v, const Normal3<T> &n2) {
  return (Dot(v, n2) < 0.f) ? -v : v;
}

template<typename T>
Normal3<T> Abs(const Normal3<T> &v) {
  return Normal3<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z));
}

template<typename T>
inline const Point3<T> &Bounds3<T>::operator[](int i) const {
  DCHECK(i == 0 || i == 1);
  return (i == 0) ? p_min : p_max;
}

template<typename T>
inline Point3<T> &Bounds3<T>::operator[](int i) {
  DCHECK(i == 0 || i == 1);
  return (i == 0) ? p_min : p_max;
}

template<typename T>
Bounds3<T> Union(const Bounds3<T> &b, const Point3<T> &p) {
  Bounds3<T> ret;
  ret.p_min = Min(b.p_min, p);
  ret.p_max = Max(b.p_max, p);
  return ret;
}

template<typename T>
Bounds3<T> Union(const Bounds3<T> &b1, const Bounds3<T> &b2) {
  Bounds3<T> ret;
  ret.p_min = Min(b1.p_min, b2.p_min);
  ret.p_max = Max(b1.p_max, b2.p_max);
  return ret;
}

template<typename T>
Bounds3<T> Intersect(const Bounds3<T> &b1, const Bounds3<T> &b2) {
  // Important: assign to p_min/p_max directly and don't run the Bounds2()
  // constructor, since it takes min/max of the points passed to it.  In
  // turn, that breaks returning an invalid bound for the case where we
  // intersect non-overlapping bounds (as we'd like to happen).
  Bounds3<T> ret;
  ret.p_min = Max(b1.p_min, b2.p_min);
  ret.p_max = Min(b1.p_max, b2.p_max);
  return ret;
}

template<typename T>
bool Overlaps(const Bounds3<T> &b1, const Bounds3<T> &b2) {
  bool x = (b1.p_max.x >= b2.p_min.x) && (b1.p_min.x <= b2.p_max.x);
  bool y = (b1.p_max.y >= b2.p_min.y) && (b1.p_min.y <= b2.p_max.y);
  bool z = (b1.p_max.z >= b2.p_min.z) && (b1.p_min.z <= b2.p_max.z);
  return (x && y && z);
}

template<typename T>
bool Inside(const Point3<T> &p, const Bounds3<T> &b) {
  return (p.x >= b.p_min.x && p.x <= b.p_max.x && p.y >= b.p_min.y &&
      p.y <= b.p_max.y && p.z >= b.p_min.z && p.z <= b.p_max.z);
}

template<typename T>
bool InsideExclusive(const Point3<T> &p, const Bounds3<T> &b) {
  return (p.x >= b.p_min.x && p.x < b.p_max.x && p.y >= b.p_min.y &&
      p.y < b.p_max.y && p.z >= b.p_min.z && p.z < b.p_max.z);
}

template<typename T, typename U>
inline Bounds3<T> Expand(const Bounds3<T> &b, U delta) {
  return Bounds3<T>(b.p_min - Vector3<T>(delta, delta, delta),
                    b.p_max + Vector3<T>(delta, delta, delta));
}

// Minimum squared distance from point to box; returns zero if point is
// inside.
template<typename T, typename U>
inline Float DistanceSquared(const Point3<T> &p, const Bounds3<U> &b) {
  Float dx = std::max({Float(0), b.p_min.x - p.x, p.x - b.p_max.x});
  Float dy = std::max({Float(0), b.p_min.y - p.y, p.y - b.p_max.y});
  Float dz = std::max({Float(0), b.p_min.z - p.z, p.z - b.p_max.z});
  return dx * dx + dy * dy + dz * dz;
}

template<typename T, typename U>
inline Float Distance(const Point3<T> &p, const Bounds3<U> &b) {
  return std::sqrt(DistanceSquared(p, b));
}

inline Bounds2iIterator begin(const Bounds2i &b) {
  return Bounds2iIterator(b, b.p_min);
}

inline Bounds2iIterator end(const Bounds2i &b) {
  // Normally, the ending point is at the minimum x value and one past
  // the last valid y value.
  Point2i pEnd(b.p_min.x, b.p_max.y);
  // However, if the bounds are degenerate, override the end point to
  // equal the start point so that any attempt to iterate over the bounds
  // exits out immediately.
  if (b.p_min.x >= b.p_max.x || b.p_min.y >= b.p_max.y)
    pEnd = b.p_min;
  return Bounds2iIterator(b, pEnd);
}

template<typename T>
Bounds2<T> Union(const Bounds2<T> &b, const Point2<T> &p) {
  Bounds2<T> ret;
  ret.p_min = Min(b.p_min, p);
  ret.p_max = Max(b.p_max, p);
  return ret;
}

template<typename T>
Bounds2<T> Union(const Bounds2<T> &b, const Bounds2<T> &b2) {
  Bounds2<T> ret;
  ret.p_min = Min(b.p_min, b2.p_min);
  ret.p_max = Max(b.p_max, b2.p_max);
  return ret;
}

template<typename T>
Bounds2<T> Intersect(const Bounds2<T> &b1, const Bounds2<T> &b2) {
  // Important: assign to p_min/p_max directly and don't run the Bounds2()
  // constructor, since it takes min/max of the points passed to it.  In
  // turn, that breaks returning an invalid bound for the case where we
  // intersect non-overlapping bounds (as we'd like to happen).
  Bounds2<T> ret;
  ret.p_min = Max(b1.p_min, b2.p_min);
  ret.p_max = Min(b1.p_max, b2.p_max);
  return ret;
}

template<typename T>
bool Overlaps(const Bounds2<T> &ba, const Bounds2<T> &bb) {
  bool x = (ba.p_max.x >= bb.p_min.x) && (ba.p_min.x <= bb.p_max.x);
  bool y = (ba.p_max.y >= bb.p_min.y) && (ba.p_min.y <= bb.p_max.y);
  return (x && y);
}

template<typename T>
bool Inside(const Point2<T> &pt, const Bounds2<T> &b) {
  return (pt.x >= b.p_min.x && pt.x <= b.p_max.x && pt.y >= b.p_min.y &&
      pt.y <= b.p_max.y);
}

template<typename T>
bool InsideExclusive(const Point2<T> &pt, const Bounds2<T> &b) {
  return (pt.x >= b.p_min.x && pt.x < b.p_max.x && pt.y >= b.p_min.y &&
      pt.y < b.p_max.y);
}

template<typename T, typename U>
Bounds2<T> Expand(const Bounds2<T> &b, U delta) {
  return Bounds2<T>(b.p_min - Vector2<T>(delta, delta),
                    b.p_max + Vector2<T>(delta, delta));
}

template<typename T>
inline bool Bounds3<T>::IntersectP(const Ray &ray, Float *hitt0,
                                   Float *hitt1) const {
  Float t0 = 0, t1 = ray.t_max;
  for (int i = 0; i < 3; ++i) {
    // Update interval for _i_th bounding box slab
    Float inv_ray_dir = 1 / ray.d[i];
    Float t_near = (p_min[i] - ray.o[i]) * inv_ray_dir;
    Float t_far = (p_max[i] - ray.o[i]) * inv_ray_dir;

    // Update parametric interval from slab intersection $t$ values
    if (t_near > t_far) std::swap(t_near, t_far);

    // Update _t_far_ to ensure robust ray--bounds intersection
    t_far *= 1 + 2 * gamma(3);
    t0 = t_near > t0 ? t_near : t0;
    t1 = t_far < t1 ? t_far : t1;
    if (t0 > t1) return false;
  }
  if (hitt0) *hitt0 = t0;
  if (hitt1) *hitt1 = t1;
  return true;
}

template<typename T>
inline bool Bounds3<T>::IntersectP(const Ray &ray, const Vector3f &invDir,
                                   const int dir_is_neg[3]) const {
  const Bounds3f &bounds = *this;
  // Check for ray intersection against $x$ and $y$ slabs
  Float t_min = (bounds[dir_is_neg[0]].x - ray.o.x) * invDir.x;
  Float t_max = (bounds[1 - dir_is_neg[0]].x - ray.o.x) * invDir.x;
  Float ty_min = (bounds[dir_is_neg[1]].y - ray.o.y) * invDir.y;
  Float ty_max = (bounds[1 - dir_is_neg[1]].y - ray.o.y) * invDir.y;

  // Update _t_max_ and _ty_max_ to ensure robust bounds intersection
  t_max *= 1 + 2 * gamma(3);
  ty_max *= 1 + 2 * gamma(3);
  if (t_min > ty_max || ty_min > t_max) return false;
  if (ty_min > t_min) t_min = ty_min;
  if (ty_max < t_max) t_max = ty_max;

  // Check for ray intersection against $z$ slab
  Float tz_min = (bounds[dir_is_neg[2]].z - ray.o.z) * invDir.z;
  Float tz_max = (bounds[1 - dir_is_neg[2]].z - ray.o.z) * invDir.z;

  // Update _tz_max_ to ensure robust bounds intersection
  tz_max *= 1 + 2 * gamma(3);
  if (t_min > tz_max || tz_min > t_max) return false;
  if (tz_min > t_min) t_min = tz_min;
  if (tz_max < t_max) t_max = tz_max;
  return (t_min < ray.t_max) && (t_max > 0);
}

inline Point3f OffsetRayOrigin(const Point3f &p, const Vector3f &p_error,
                               const Normal3f &n, const Vector3f &w) {
  Float d = Dot(Abs(n), p_error);
#ifdef CHIHAYA_FLOAT_AS_DOUBLE
  // We have tons of precision; for now bump up the offset a bunch just
    // to be extra sure that we start on the right side of the surface
    // (In case of any bugs in the epsilons code...)
    d *= 1024.;
#endif
  Vector3f offset = d * Vector3f(n);
  if (Dot(w, n) < 0) offset = -offset;
  Point3f po = p + offset;
  // Round offset point _po_ away from _p_
  for (int i = 0; i < 3; ++i) {
    if (offset[i] > 0)
      po[i] = NextFloatUp(po[i]);
    else if (offset[i] < 0)
      po[i] = NextFloatDown(po[i]);
  }
  return po;
}

inline Vector3f SphericalDirection(Float sin_theta, Float cos_theta, Float phi) {
  return Vector3f(sin_theta * std::cos(phi), sin_theta * std::sin(phi),
                  cos_theta);
}

inline Vector3f SphericalDirection(Float sin_theta, Float cos_theta, Float phi,
                                   const Vector3f &x, const Vector3f &y,
                                   const Vector3f &z) {
  return sin_theta * std::cos(phi) * x + sin_theta * std::sin(phi) * y +
      cos_theta * z;
}

inline Float SphericalTheta(const Vector3f &v) {
  return std::acos(Clamp(v.z, -1, 1));
}

inline Float SphericalPhi(const Vector3f &v) {
  Float p = std::atan2(v.y, v.x);
  return (p < 0) ? (p + 2 * Pi) : p;
}

}

#endif //CHIHAYA_SRC_CORE_GEOMETRY_H_
