/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef CHIHAYA_SRC_CORE_PARALLEL_H_
#define CHIHAYA_SRC_CORE_PARALLEL_H_

#include <functional>
#include "geometry.h"

namespace chihaya {

void ParallelFor2D(std::function<void(Point2i)> func, const Point2i &count);

}

#endif //CHIHAYA_SRC_CORE_PARALLEL_H_
