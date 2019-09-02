/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef CHIHAYA_INCLUDE_CHIHAYA_CHIHAYA_H_
#define CHIHAYA_INCLUDE_CHIHAYA_CHIHAYA_H_

#include <iostream>
#include <cmath>
#include <limits>
#include <chrono>
#include <algorithm>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>

#include <fmt/format.h>
#include <glog/logging.h>

#define CHIHAYA_NAMESPACE_BEGIN namespace chihaya {

#define CHIHAYA_NAMESPACE_END }

CHIHAYA_NAMESPACE_BEGIN

//******************************************************************************
//                                 Types
//******************************************************************************

using uchar = unsigned char;
using uint = unsigned int;

#ifdef _WIN64
#define FORCE_INLINE __forceinline
#else
#define FORCE_INLINE inline __attribute__((always_inline))
#endif

using float32 = float;
using float64 = double;

#ifdef USE_DOUBLE
using real = float64;
#else
using real = float32;
#endif

CHIHAYA_NAMESPACE_END

#endif //CHIHAYA_INCLUDE_CHIHAYA_CHIHAYA_H_
