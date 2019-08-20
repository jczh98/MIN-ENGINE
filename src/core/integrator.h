/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef CHIHAYA_SRC_CORE_INTEGRATOR_H_
#define CHIHAYA_SRC_CORE_INTEGRATOR_H_

#include "scene.h"
#include "sampler.h"
#include "camera.h"

namespace chihaya {

class Integrator {
 public:
  virtual void Render(const Scene &scene) = 0;
};

class SamplerIntegrator : public Integrator {
 public:
  SamplerIntegrator(std::shared_ptr<Camera> camera,
      std::shared_ptr<Sampler> sampler);
  virtual void Preprocess(const Scene &scene, Sampler &sampler) = 0;
  void Render(const Scene &scene);
 protected:
  std::shared_ptr<const Camera> camera;
 private:
  std::shared_ptr<Sampler> sampler_;
};

}
#endif //CHIHAYA_SRC_CORE_INTEGRATOR_H_
