/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef MIN_INCLUDE_MIN_MATH_COMMON_H_
#define MIN_INCLUDE_MIN_MATH_COMMON_H_

#include <min/min.h>

MIN_NAMESPACE_BEGIN

inline real Lerp(real t, real v1, real v2) { return (1 - t) * v1 + t * v2; }

MIN_NAMESPACE_END

#endif //MIN_INCLUDE_MIN_MATH_COMMON_H_
