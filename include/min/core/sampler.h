/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef MIN_INCLUDE_MIN_CORE_SAMPLER_H_
#define MIN_INCLUDE_MIN_CORE_SAMPLER_H_

#include <min/min.h>
#include "camera.h"

MIN_NAMESPACE_BEGIN

class Sampler {
 public:
  virtual ~Sampler();
  Sampler(int64_t samples_per_pixel);
  virtual void StartPixel(const Vector2i &p);
  virtual real Get1D() = 0;
  virtual Vector2i Get2D() = 0;
  CameraSample GetCameraSample(const Vector2i &pRaster);
  void Request1DArray(int n);
  void Request2DArray(int n);
  virtual int RoundCount(int n) const { return n; }
  const real *Get1DArray(int n);
  const Vector2f *Get2DArray(int n);
  virtual bool StartNextSample();
  virtual std::unique_ptr<Sampler> Clone(int seed) = 0;
  virtual bool SetSampleNumber(int64_t sampleNum);

  int64_t CurrentSampleNumber() const { return current_pixel_sample_index; }

  const int64_t samples_per_pixel;
 protected:
  Vector2i current_pixel;
  int64_t current_pixel_sample_index;
};
MIN_NAMESPACE_END

#endif //MIN_INCLUDE_MIN_CORE_SAMPLER_H_
