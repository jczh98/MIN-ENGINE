/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef MIN_INCLUDE_MIN_CORE_FILTER_H_
#define MIN_INCLUDE_MIN_CORE_FILTER_H_

#include <min/min.h>
#include "object.h"

MIN_NAMESPACE_BEGIN

class Filter : public MinObject{
 public:
  virtual Float Evaluate(Float x) const = 0;
  Float radius() const { return radius_; }

  ClassType GetClassType() const override {
    return ClassType::kFilter;
  }

 private:
  Float radius_;
};

MIN_NAMESPACE_END

#endif //MIN_INCLUDE_MIN_CORE_FILTER_H_