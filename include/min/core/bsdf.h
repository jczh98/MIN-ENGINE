/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef MIN_INCLUDE_MIN_CORE_BSDF_H_
#define MIN_INCLUDE_MIN_CORE_BSDF_H_

#include <min/min.h>

MIN_NAMESPACE_BEGIN

struct BSDFQueryRecord {

  BSDFQueryRecord(const Vector3 &wi) : wi(wi) {}

  // Incident direction
  Vector3 wi;
  // Outgoing direction
  Vector3 wo;
  // Relative refractive index in the sampled direction
  Float eta;
};

class BSDF {
 public:
  virtual Vector3 Sample(BSDFQueryRecord &record, const Vector2 &sample) const = 0;

  virtual Vector3 Evaluate(const BSDFQueryRecord &record) const = 0;

  // Compute the probability density function
  virtual Float Pdf(const BSDFQueryRecord &record) const = 0;

  virtual bool IsDiffuse() const { return false; }
};
MIN_NAMESPACE_END

#endif //MIN_INCLUDE_MIN_CORE_BSDF_H_
