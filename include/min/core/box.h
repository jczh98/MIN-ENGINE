/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef MIN_INCLUDE_MIN_CORE_BOX_H_
#define MIN_INCLUDE_MIN_CORE_BOX_H_

#include <min/min.h>
#include <min/math/common.h>

#include "ray.h"

MIN_NAMESPACE_BEGIN

template <typename T>
class Bounds3 {
 public:
  Bounds3() {
    T minNum = std::numeric_limits<T>::lowest();
    T maxNum = std::numeric_limits<T>::max();
    pMin = Eigen::Vector3<T>(maxNum, maxNum, maxNum);
    pMax = Eigen::Vector3<T>(minNum, minNum, minNum);
  }
  explicit Bounds3(const Eigen::Vector3<T> &p) : pMin(p), pMax(p) {}
  Bounds3(const Eigen::Vector3<T> &p1, const Eigen::Vector3<T> &p2)
      : pMin(std::min(p1.x(), p2.x()), std::min(p1.y(), p2.y()),
             std::min(p1.z(), p2.z())),
        pMax(std::max(p1.x(), p2.x()), std::max(p1.y(), p2.y()),
             std::max(p1.z(), p2.z())) {}
  const Eigen::Vector3<T> &operator[](int i) const;
  Eigen::Vector3<T> &operator[](int i);
  bool operator==(const Bounds3<T> &b) const {
    return b.pMin == pMin && b.pMax == pMax;
  }
  bool operator!=(const Bounds3<T> &b) const {
    return b.pMin != pMin || b.pMax != pMax;
  }

  Eigen::Vector3<T> Corner(int corner) const {
    DCHECK(corner >= 0 && corner < 8);
    return Eigen::Vector3<T>((*this)[(corner & 1)].x(),
                     (*this)[(corner & 2) ? 1 : 0].y(),
                     (*this)[(corner & 4) ? 1 : 0].z());
  }
  Eigen::Vector3<T> Diagonal() const { return pMax - pMin; }
  T SurfaceArea() const {
    Eigen::Vector3<T> d = Diagonal();
    return 2 * (d.x() * d.y() + d.x() * d.z() + d.y() * d.z());
  }
  T Volume() const {
    Eigen::Vector3<T> d = Diagonal();
    return d.x() * d.y() * d.z();
  }
  int MaximumExtent() const {
    Eigen::Vector3<T> d = Diagonal();
    if (d.x() > d.y() && d.x() > d.z())
      return 0;
    else if (d.y() > d.z())
      return 1;
    else
      return 2;
  }
  Eigen::Vector3<T> Lerp(const Vector3f &t) const {
    return Eigen::Vector3<T>(min::Lerp(t.x(), pMin.x(), pMax.x()),
                     min::Lerp(t.y(), pMin.y(), pMax.y()),
                     min::Lerp(t.z(), pMin.z(), pMax.z()));
  }
  Eigen::Vector3<T> Offset(const Eigen::Vector3<T> &p) const {
    Eigen::Vector3<T> o = p - pMin;
    if (pMax.x() > pMin.x()) o.x() /= pMax.x() - pMin.x();
    if (pMax.y() > pMin.y()) o.y() /= pMax.y() - pMin.y();
    if (pMax.z() > pMin.z()) o.z() /= pMax.z() - pMin.z();
    return o;
  }
  void BoundingSphere(Eigen::Vector3<T> *center, real *radius) const {
    *center = (pMin + pMax) / 2;
    *radius = Inside(*center, *this) ? Distance(*center, pMax) : 0;
  }
  template <typename U>
  explicit operator Bounds3<U>() const {
    return Bounds3<U>((Eigen::Vector3<U>)pMin, (Eigen::Vector3<U>)pMax);
  }
  bool IntersectP(const Ray &ray, real *hitt0 = nullptr,
                  real *hitt1 = nullptr) const;
  inline bool IntersectP(const Ray &ray, const Vector3f &invDir,
                         const int dirIsNeg[3]) const;
  friend std::ostream &operator<<(std::ostream &os, const Bounds3<T> &b) {
    os << "[ " << b.pMin << " - " << b.pMax << " ]";
    return os;
  }
  Eigen::Vector3<T> pMin, pMax;
};

template <typename T>
FORCE_INLINE const Vector3<T> &Bounds3<T>::operator[](int i) const {
  DCHECK(i == 0 || i == 1);
  return i == 0 ? pMin : pMax;
}

template <typename T>
FORCE_INLINE Vector3<T> &Bounds3<T>::operator[](int i) {
  DCHECK(i == 0 || i == 1);
  return i == 0 ? pMin : pMax;
}

using Bounds3f = Bounds3<real>;
using Bounds3i = Bounds3<int>;

MIN_NAMESPACE_END
#endif //MIN_INCLUDE_MIN_CORE_BOX_H_
