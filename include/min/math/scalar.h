/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef MIN_INCLUDE_MIN_MATH_SCALAR_H_
#define MIN_INCLUDE_MIN_MATH_SCALAR_H_

#include <cmath>
#include <min/common/util.h>

MIN_NAMESPACE_BEGIN

#undef max
#undef min

using std::abs;
using std::acos;
using std::asin;
using std::atan;
using std::cos;
using std::floor;
using std::max;
using std::min;
using std::sin;
using std::tan;

const Float pi{acosf(-1.0_f)};
const Float eps = 1e-6_f;

template <int I, typename T>
constexpr MIN_FORCE_INLINE T pow(T a) noexcept {
  T ret(1);
  for (int i = 0; i < I; i++) {
    ret *= a;
  }
  return ret;
}

template <typename T>
MIN_FORCE_INLINE T clamp(const T &a, const T &min, const T &max) noexcept {
  if (a < min)
    return min;
  if (a > max)
    return max;
  return a;
}

MIN_FORCE_INLINE uint32 rand_int() noexcept {
  static unsigned int x = 123456789, y = 362436069, z = 521288629, w = 88675123;
  unsigned int t = x ^ (x << 11);
  x = y;
  y = z;
  z = w;
  return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
}

MIN_FORCE_INLINE uint64 rand_int64() noexcept {
  return ((uint64)rand_int() << 32) + rand_int();
}

// inline float frand() { return (float)rand() / (RAND_MAX + 1); }
MIN_FORCE_INLINE float32 rand() noexcept {
  return rand_int() * (1.0_f / 4294967296.0f);
}

inline int is_prime(int a) noexcept {
  assert(a >= 2);
  for (int i = 2; i * i <= a; i++) {
    if (a % i == 0)
      return false;
  }
  return true;
}
MIN_NAMESPACE_END

#endif //MIN_INCLUDE_MIN_MATH_SCALAR_H_
