/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef CHIHAYA_SRC_CORE_HITABLE_H_
#define CHIHAYA_SRC_CORE_HITABLE_H_

#include "common.h"
#include "ray.h"

MIN_NAMESPACE_BEGIN

class Material;

struct HitRecord {
  Float t;
  Vector3f p;
  Vector3f normal;
  Material *mat_ptr;
};

class Hitable {
 public:
  virtual bool hit(const Ray &ray, Float t_min, Float t_max, HitRecord &rec) const = 0;
};

MIN_NAMESPACE_END

#endif //CHIHAYA_SRC_CORE_HITABLE_H_
