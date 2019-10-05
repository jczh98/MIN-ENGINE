/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef MIN_INCLUDE_MIN_CORE_FILTER_H_
#define MIN_INCLUDE_MIN_CORE_FILTER_H_

#include <min/min.h>

MIN_NAMESPACE_BEGIN

class Filter {
 public:
  virtual real Evaluate(real x) const = 0;
  real radius() const { return radius_; }
 private:
  real radius_;
};

MIN_NAMESPACE_END

#endif //MIN_INCLUDE_MIN_CORE_FILTER_H_
