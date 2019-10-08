/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#ifndef MIN_INCLUDE_MIN_CORE_MESH_H_
#define MIN_INCLUDE_MIN_CORE_MESH_H_

#include <min/min.h>
#include "object.h"
#include "bsdf.h"
#include "aabb.h"
#include "ray.h"

MIN_NAMESPACE_BEGIN

class Mesh : public MinObject {
 public:
  virtual ~Mesh();
  virtual void Activate();

  uint32_t triangle_count() const { return (uint32_t) f_.cols(); }
  uint32_t vertex_count() const { return (uint32_t) v_.cols(); }

  // Uniformaly sample a position on the mesh with
  // respect to surface area. Returns both position and normal
  void SamplePosition(const Vector2 sample, Vector3 &p, Vector3 &n) const;

  // Return the surface area of the given triangle
  Float SurfaceArea(uint32_t index) const;

  const BoundingBox &bounding_box() const { return aabb_; }

  BoundingBox GetBoundingBox(uint32_t index) const;

  Vector3 GetCentroid(uint32_t index) const;

  bool RayIntersect(uint32_t index, const Ray &ray, Float &u, Float &v, Float &t) const;

  MatrixXf vertex_positions() const { return v_; }

  MatrixXf vertex_normals() const { return n_; }

  MatrixXf vertex_texcoords() const { return uv_; }

  MatrixXu indices() const { return f_; }

  std::shared_ptr<BSDF> bsdf() const { return bsdf_; };

  virtual void AddChild(MinObject *child);

 protected:
  Mesh();
 private:
  MatrixXf v_; // Vertex positions
  MatrixXf n_; // Vertex normals
  MatrixXf uv_; // vertex texture coordinates
  MatrixXu f_; // faces
  std::shared_ptr<BSDF> bsdf_; // bsdf of the surface
  BoundingBox aabb_;
};

MIN_NAMESPACE_END

#endif //MIN_INCLUDE_MIN_CORE_MESH_H_
