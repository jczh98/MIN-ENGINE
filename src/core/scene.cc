/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#include "scene.h"

namespace chihaya {

Scene::Scene(std::shared_ptr<chihaya::Primitive> aggregate, const std::vector<std::shared_ptr<Light>> &lights) :
    aggregate_{aggregate},
    lights{lights} {
  world_bound_ = aggregate_->WorldBound();
  for (const auto &light : lights) {
    light->Preprocess(*this);
  }
}

const Bounds3f& Scene::word_bound() const {
  return world_bound_;
}

bool Scene::Intersect(const Ray &ray, SurfaceInteraction *isect) const {
  return aggregate_->Intersect(ray, isect);
}

bool Scene::IntersectP(const Ray &ray) const {
  return aggregate_->IntersectP(ray);
}

}
