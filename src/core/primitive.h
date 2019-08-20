/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef CHIHAYA_SRC_CORE_PRIMITIVE_H_
#define CHIHAYA_SRC_CORE_PRIMITIVE_H_

#include "geometry.h"

namespace chihaya {

struct Primitive {
  virtual Bounds3f WorldBound() const = 0;
};

}

#endif //CHIHAYA_SRC_CORE_PRIMITIVE_H_
