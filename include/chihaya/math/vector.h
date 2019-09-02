/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef CHIHAYA_INCLUDE_CHIHAYA_MATH_VECTOR_H_
#define CHIHAYA_INCLUDE_CHIHAYA_MATH_VECTOR_H_

#include <chihaya/chihaya.h>

CHIHAYA_NAMESPACE_BEGIN

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

CHIHAYA_NAMESPACE_END

#endif //CHIHAYA_INCLUDE_CHIHAYA_MATH_VECTOR_H_
