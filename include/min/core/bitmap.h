/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef MIN_INCLUDE_MIN_CORE_BITMAP_H_
#define MIN_INCLUDE_MIN_CORE_BITMAP_H_

#include <min/min.h>
#include "color.h"

MIN_NAMESPACE_BEGIN

class Bitmap : public Eigen::Array<Color3f, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> {
 public:
  typedef Eigen::Array<Color3f, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> Base;

  // Allocate a new bitmap of the specified size
  explicit Bitmap(const Vector2i &size = Vector2i(0, 0)) : Base(size.y(), size.x()) {}

  // Load an file with the specified filename
  Bitmap(const std::string filename);

  // Save the bitmap with the specified filename
  void Save(const std::string &filename);
};
MIN_NAMESPACE_END

#endif //MIN_INCLUDE_MIN_CORE_BITMAP_H_
