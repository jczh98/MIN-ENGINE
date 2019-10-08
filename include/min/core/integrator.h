/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef MIN_INCLUDE_MIN_CORE_INTEGRATOR_H_
#define MIN_INCLUDE_MIN_CORE_INTEGRATOR_H_

#include <min/min.h>
#include "ray.h"
#include "scene.h"
#include "sampler.h"
#include "color.h"

MIN_NAMESPACE_BEGIN

class Integrator {
 public:
  virtual ~Integrator();
  virtual void Render(const Scene &scene) = 0;
};

class SamplerIntegrator : public Integrator {
 public:
  // Perform an optional preprocess operation
  virtual void PreProcess(const Scene &scene) = 0;
  // Sample the incident radiance along a ray
  virtual Color3f Li(const Scene &scene, Sampler &sampler, const Ray &ray) const = 0;
};

MIN_NAMESPACE_END

#endif //MIN_INCLUDE_MIN_CORE_INTEGRATOR_H_
