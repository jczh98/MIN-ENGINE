/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef CHIHAYA_SRC_CORE_COMMON_H_
#define CHIHAYA_SRC_CORE_COMMON_H_

#include <iostream>
#include <cmath>
#include <limits>

#include <fmt/format.h>
#include "glog/logging.h"

namespace chihaya {

using Float = double ;

#define Infinity std::numeric_limits<Float>::infinity()

#define CHIHAYA_NAMESPACE_BEGIN namespace chihaya {
#define CHIHAYA_NAMESPACE_END }

template <typename T>
inline bool isNaN(const T x) {
  return std::isnan(x);
}
template <>
inline bool isNaN(const int x) {
  return false;
}


}

#endif //CHIHAYA_SRC_CORE_COMMON_H_
