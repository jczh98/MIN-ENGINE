/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#include <min/core/block.h>
#include <min/core/aabb.h>

MIN_NAMESPACE_BEGIN

ImageBlock::ImageBlock(const Vector2i &size, const Filter &filter) : offset(0, 0),
                                                                     size(size) {
  filter_radius_ = filter.radius();
  border_size = (int) std::ceil(filter_radius_ - 0.5f);
  filter_ = new Float[MIN_FILTER_RESOLUTION + 1];
  for (int i = 0; i < MIN_FILTER_RESOLUTION; i++) {
    Float pos = (filter_radius_*i)/MIN_FILTER_RESOLUTION;
    filter_[i] = filter.Evaluate(pos);
  }
  filter_[MIN_FILTER_RESOLUTION] = 0.0f;
  lookup_factor_ = MIN_FILTER_RESOLUTION/filter_radius_;
  int weight_size = (int) std::ceil(2*filter_radius_) + 1;
  weights_x_ = new Float[weight_size];
  weights_y_ = new Float[weight_size];
  memset(weights_x_, 0, sizeof(Float)*weight_size);
  memset(weights_y_, 0, sizeof(Float)*weight_size);
}

ImageBlock::~ImageBlock() {
  delete[] filter_;
  delete[] weights_y_;
  delete[] weights_x_;
}

std::unique_ptr<Bitmap> ImageBlock::ToBitmap() const {
  auto result = std::make_unique<Bitmap>(Bitmap(size));
  for (int y = 0; y < size.y(); y++) {
    for (int x = 0; x < size.x(); x++) {
      result->coeffRef(y, x) = coeff(y + border_size, x + border_size).DivideByFilterWeight();
    }
  }
  return result;
}

void ImageBlock::FromBitmap(const Bitmap &bitmap) {
  if (bitmap.cols()!=cols() || bitmap.rows()!=rows())
    throw std::runtime_error("Invalid bitmap dimensions");

  for (int y = 0; y < size.y(); y++) {
    for (int x = 0; x < size.x(); x++) {
      coeffRef(y, x) << bitmap.coeff(y, x), 1;
    }
  }
}

void ImageBlock::Put(const Vector2 &pos, const Color3f &value) {
  if (!value.valid()) {
    std::cerr << "Integrator: computed an invalid radiance value: " << value.string() << std::endl;
    return;
  }
  Vector2 pos_within(
      pos.x() - 0.5f - (offset.x() - border_size),
      pos.y() - 0.5f - (offset.y() - border_size)
      );
}
void ImageBlock::Put(ImageBlock &b) {

}

MIN_NAMESPACE_END

 
