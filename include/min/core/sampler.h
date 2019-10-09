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
#include "block.h"
#include "object.h"

MIN_NAMESPACE_BEGIN

class Sampler : public MinObject{
 public:
  virtual ~Sampler();
  virtual std::unique_ptr<Sampler> Clone() const = 0;
  virtual void Prepare(const ImageBlock &block) = 0;
  virtual void Generate() = 0;
  // Next sample
  virtual void Advance() = 0;
  // Retrieve the next component value from current sample
  virtual Float Next1D() = 0;
  // Retrieve the next two component value from current sample
  virtual Vector2 Next2D() = 0;
  ClassType GetClassType() const { return kSampler; }

  size_t sample_count;
};
MIN_NAMESPACE_END

#endif //MIN_INCLUDE_MIN_CORE_SAMPLER_H_
