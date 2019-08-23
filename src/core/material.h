/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef CHIHAYA_SRC_CORE_MATERIAL_H_
#define CHIHAYA_SRC_CORE_MATERIAL_H_

#include "common.h"
#include "hitable.h"

CHIHAYA_NAMESPACE_BEGIN

Vector3f RandomInUnitSphere() {
  Vector3f p;
  do {
    p = Vector3f(drand48(), drand48(), drand48()) * 2.0 - Vector3f(1, 1, 1);
  } while (p.LengthSquared() >= 1.0);
  return p;
}

class Material {
 public:
  virtual bool Scatter(const Ray &ray, const HitRecord &rec, Vector3f &attenuation, Ray &scattered) const = 0;
};

class Lambertian: public Material {
 public:
  Lambertian(const Vector3f &a) : albedo{a} {}

  virtual bool Scatter(const Ray &ray, const HitRecord &rec, Vector3f &attenuation, Ray &scattered) const {
    Vector3f target = rec.p + rec.normal + RandomInUnitSphere();
    scattered = Ray(rec.p, target - rec.p);
    attenuation = albedo;
    return true;
  }

  Vector3f albedo;
};

class Metal: public Material {
 public:
  Metal(const Vector3f &a, Float f) : albedo{a} {
    if (f < 1) fuzz = f;
    else fuzz = 1;
  }

  virtual bool Scatter(const Ray &ray, const HitRecord &rec, Vector3f &attenuation, Ray &scattered) const{
    Vector3f reflected = Reflect(Normalize(ray.d), rec.normal);
    scattered = Ray(rec.p, reflected + RandomInUnitSphere() * fuzz);
    attenuation = albedo;
    return (Dot(scattered.d, rec.normal) > 0);
  }

  Vector3f Reflect(const Vector3f &v, const Vector3f &n) const {
    return v - n * 2 * Dot(v, n);
  }

  Vector3f albedo;
  Float fuzz;
};
CHIHAYA_NAMESPACE_END

#endif //CHIHAYA_SRC_CORE_MATERIAL_H_
