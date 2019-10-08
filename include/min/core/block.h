/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef MIN_INCLUDE_MIN_CORE_BLOCK_H_
#define MIN_INCLUDE_MIN_CORE_BLOCK_H_

#include <min/min.h>
#include <tbb/mutex.h>
#include "color.h"
#include "filter.h"
#include "bitmap.h"

MIN_NAMESPACE_BEGIN

class ImageBlock : public Eigen::Array<Color4f, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> {
 public:
  explicit ImageBlock(const Vector2i &size, const Filter &filter);
  ~ImageBlock();

  std::unique_ptr<Bitmap> ToBitmap() const;

  void FromBitmap(const Bitmap &bitmap);

  void Clear() {
    setConstant(Color4f());
  }

  void Put(const Vector2 &pos, const Color3f &value);

  void Put(ImageBlock &b);

  MIN_FORCE_INLINE void Lock() const { mutex_.lock(); }

  MIN_FORCE_INLINE void Unlock() const { mutex_.unlock(); }
  Vector2i offset, size;
  int border_size;
 private:
  std::shared_ptr<min::Float> filter_ = nullptr,
      weights_x_ = nullptr,
      weights_y_ = nullptr;
  min::Float filter_radius_ = 0,
      lookup_factor_ = 0;
  mutable tbb::mutex mutex_;
};
MIN_NAMESPACE_END

#endif //MIN_INCLUDE_MIN_CORE_BLOCK_H_
