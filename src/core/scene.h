/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef CHIHAYA_SRC_CORE_SCENE_H_
#define CHIHAYA_SRC_CORE_SCENE_H_

#include <memory>
#include <vector>
#include "primitive.h"
#include "light.h"

namespace chihaya {

struct Scene {

  Scene(std::shared_ptr<Primitive> aggregate,
        const std::vector<std::shared_ptr<Light>> &lights);

  const Bounds3f &word_bound() const;

  bool Intersect(const Ray &ray, SurfaceInteraction *isect) const;

  bool IntersectP(const Ray &ray) const;

  std::vector<std::shared_ptr<Light>> lights;

 private:

  std::shared_ptr<Primitive> aggregate_;

  Bounds3f world_bound_;
};

}

#endif //CHIHAYA_SRC_CORE_SCENE_H_
