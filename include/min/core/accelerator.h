/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef MIN_INCLUDE_MIN_CORE_ACCELERATOR_H_
#define MIN_INCLUDE_MIN_CORE_ACCELERATOR_H_

#include "mesh.h"
#include "intersection.h"
#include "aabb.h"
#include "ray.h"

MIN_NAMESPACE_BEGIN

class Accelerator {
 public:
  void AddMesh(std::shared_ptr<Mesh> mesh);

  void Build();

  const BoundingBox &bounding_box() const { return box_; }

  bool RayIntersect(const Ray &ray, Intersection &intersection, bool shadow) const;
 private:
  std::shared_ptr<Mesh> mesh_ = nullptr;
  BoundingBox box_;
};

MIN_NAMESPACE_END

#endif //MIN_INCLUDE_MIN_CORE_ACCELERATOR_H_
