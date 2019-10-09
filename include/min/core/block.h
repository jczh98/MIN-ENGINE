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

#define MIN_BLOCK_SIZE 32

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

class BlockGenerator {
 public:
  BlockGenerator(const Vector2i &size, int block_size);

  bool Next(ImageBlock &block);

  int blocks_left;
 private:
  enum Direction {
    kRight = 0, kDown, kLeft, kUp
  };
  Vector2i block_, num_blocks, size_;
  int block_size_, num_steps_, step_left_, direction_;
  tbb::mutex mutex_;
};
MIN_NAMESPACE_END

#endif //MIN_INCLUDE_MIN_CORE_BLOCK_H_
