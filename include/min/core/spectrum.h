/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef MIN_INCLUDE_MIN_CORE_SPECTRUM_H_
#define MIN_INCLUDE_MIN_CORE_SPECTRUM_H_

#include <min/min.h>

MIN_NAMESPACE_BEGIN

class Spectrum : public Eigen::Array3f {
  public:
    using Base = Eigen::Array3f;
    Spectrum(real value = 0.f) : Base(value, value, value) {}
    Spectrum(real r, real g, real b) : Base(r, g, b) {}
};
MIN_NAMESPACE_END

#endif //MIN_INCLUDE_MIN_CORE_SPECTRUM_H_
