/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef MIN_INCLUDE_MIN_MATH_VECTOR_H_
#define MIN_INCLUDE_MIN_MATH_VECTOR_H_

#include <min/min.h>

MIN_NAMESPACE_BEGIN

template <int dim, typename T>
class VectorND;

template <typename T>
inline bool isNaN(const T x) {
  return std::isnan(x);
}
template <>
inline bool isNaN(const int x) {
  return false;
}

MIN_NAMESPACE_END

#endif //MIN_INCLUDE_MIN_MATH_VECTOR_H_
