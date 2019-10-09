/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef MIN_INCLUDE_MIN_CORE_SCENE_H_
#define MIN_INCLUDE_MIN_CORE_SCENE_H_

#include <min/min.h>
#include "mesh.h"
#include "integrator.h"
#include "sampler.h"
#include "camera.h"
#include "accelerator.h"

MIN_NAMESPACE_BEGIN

class Scene : public MinObject {
 public:
  Scene(const PropertyList &);

  virtual ~Scene();

  // Intersect a ray against all triangles stored in the scene
  bool RayIntersect(const Ray &ray, Intersection &intersection) const {
    return accelerator->RayIntersect(ray, intersection, false);
  }

  bool RayIntersect(const Ray &ray) const {
    Intersection its;
    return accelerator->RayIntersect(ray, its, true);
  }
  // Return an axis-aligned bounding box that bounds the scene
  const BoundingBox &GetBoundingBox() const { return accelerator->bounding_box(); }
  std::shared_ptr<Integrator> integrator;
  std::shared_ptr<Sampler> sampler;
  std::shared_ptr<Camera> camera;
  std::shared_ptr<Accelerator> accelerator;

  ClassType GetClassType() const override {
    return kScene;
  }
 private:
  std::vector<Mesh *> meshes_;
};

MIN_NAMESPACE_END

#endif //MIN_INCLUDE_MIN_CORE_SCENE_H_
