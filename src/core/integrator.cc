/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#include "integrator.h"
#include "parallel.h"

namespace chihaya {

SamplerIntegrator::SamplerIntegrator(std::shared_ptr<chihaya::Camera> camera,
                                     std::shared_ptr<chihaya::Sampler> sampler) :
                                     camera{camera},
                                     sampler_{sampler} {

}

void SamplerIntegrator::Render(const Scene &scene) {
  Preprocess(scene, *sampler_);
  // Render image tiles in parallel

  // Compute number of tiles used for parallel rendering
  Bounds2i sample_bounds = camera->film->GetSampleBounds();
  Vector2i sample_extent = sample_bounds.Diagonal();
  const int tile_size = 16;
  Point2i tiles((sample_extent.x + tile_size - 1) / tile_size,
                (sample_extent.y + tile_size - 1) / tile_size);
  ParallelFor2D(
      [&](Point2i tile) {
        // Render section of image corresponding to tile
      }, tiles);
  // Save image after rendering
}

}
