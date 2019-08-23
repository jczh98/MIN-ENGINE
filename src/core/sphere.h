/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef CHIHAYA_SRC_CORE_SPHERE_H_
#define CHIHAYA_SRC_CORE_SPHERE_H_

#include "common.h"
#include "hitable.h"

CHIHAYA_NAMESPACE_BEGIN

class Sphere : public Hitable {
 public:
  Sphere(Vector3f center, Float r) : center{center}, radius{r} {};
  virtual bool hit(const Ray &ray, Float t_min, Float t_max, HitRecord &rec) const;
  Vector3f center;
  Float radius;

};

CHIHAYA_NAMESPACE_END

#endif //CHIHAYA_SRC_CORE_SPHERE_H_
