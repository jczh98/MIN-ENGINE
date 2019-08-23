/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#include "sphere.h"

CHIHAYA_NAMESPACE_BEGIN

bool Sphere::hit(const chihaya::Ray &ray, chihaya::Float t_min, chihaya::Float t_max, chihaya::HitRecord &rec) const {
  Vector3f oc = ray.o - center;
  Float a = Dot(ray.d, ray.d);
  Float b = Dot(oc, ray.d);
  Float c = Dot(oc, oc) - radius * radius;
  Float discriminant = b * b - a * c;
  if (discriminant > 0) {
    Float temp = (-b - sqrt(b * b - a * c)) / a;
    if (temp < t_max && temp > t_min) {
      rec.t = temp;
      rec.p = ray(rec.t);
      rec.normal = (rec.p - center) / radius;
      return true;
    }
    temp = (-b + sqrt(discriminant)) / a;
    if (temp < t_max && temp > t_min) {
      rec.t = temp;
      rec.p = ray(rec.t);
      rec.normal = (rec.p - center) / radius;
      return true;
    }
  }
  return false;
}

CHIHAYA_NAMESPACE_END
