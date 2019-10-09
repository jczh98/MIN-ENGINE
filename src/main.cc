/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#include <min/io/resolver.h>
#include <min/core/parser.h>
#include <min/core/scene.h>
#include <min/core/block.h>
#include <min/core/timer.h>
#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>

using namespace min;

void RenderBlock(const Scene &scene, Sampler &sampler, ImageBlock &block) {
  Vector2i offset = block.offset;
  Vector2i size = block.size;
  block.Clear();
  for (int y = 0; y < size.y(); y++) {
    for (int x = 0; x < size.x(); x++) {
      for (uint32_t i = 0; i < sampler.sample_count; i++) {
        Vector2 current = Vector2(x + offset.x(), y + offset.y());
        Vector2 pixel_sample = Vector2(current + sampler.Next2D());
        Vector2 aperture_sample = sampler.Next2D();
        // Sample a ray from the camera
        Ray ray;
        Color3f value = scene.camera->SampleRay(ray, pixel_sample, aperture_sample);
        // Incident radiance
        value *= scene.integrator->Li(scene, sampler, ray);
        // Store in the image block
        block.Put(pixel_sample, value);
      }
    }
  }
}

void Render(Scene *scene, const std::string &filename) {
  auto camera = scene->camera;
  Vector2i output_size = camera->output_size;
  scene->integrator->Preprocess(*scene);

  BlockGenerator block_generator(output_size, MIN_BLOCK_SIZE);

  ImageBlock result(output_size, *camera->filter);
  result.Clear();

  std::thread render_thread([&] {
    std::cout << "Rendering...";
    std::cout.flush();
    Timer timer;

    tbb::blocked_range<int> range(0, block_generator.blocks_left);


    auto map = [&](const tbb::blocked_range<int> &range) {
      // Allocate memory for a small image block to be rendered
      // by current thread
      ImageBlock block(Vector2i(MIN_BLOCK_SIZE), *camera->filter);

      // clone of the sampler for the current thread
      std::unique_ptr<Sampler> sampler(scene->sampler->Clone());

      for (int i = range.begin(); i < range.end(); i++) {
        // Request an image block
        block_generator.Next(block);
        // Inform the sampler
        sampler->Prepare(block);
        // Render all pixels in block
        RenderBlock(*scene, *sampler, block);

        // Add it to the big block that represents the entire image
        result.Put(block);
      }
    };

    tbb::parallel_for(range, map);

    std::cout << "Done. (took " << timer.ElapsedString() << ")" << std::endl;
  });

  // Enter GUI

  render_thread.join();

  delete scene;

  std::unique_ptr<Bitmap> bitmap(result.ToBitmap());
  std::string output_name = filename;
  size_t last_dot = output_name.find_last_of(".");
  if (last_dot != std::string::npos) {
    output_name.erase(last_dot, std::string::npos);
  }
  output_name += ".exr";
  // Save using openexr
  bitmap->Save(output_name);
}

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Syntax: " << argv[0] << " <scene.xml>" << std::endl;
    return -1;
  }
  fs::path path(argv[1]);
  try {
    if (path.extension() == ".xml") {
      GetFileResolver()->Append(path.parent_path());
      std::unique_ptr<min::MinObject> root(LoadFromXML(argv[1]));
      if (root->GetClassType() == MinObject::kScene) {
        Render(static_cast<Scene *>(root.get()), argv[1]);
      }
    }
  } catch (const std::exception &e) {
    std::cerr << "Fatal error: " << e.what() << std::endl;
    return -1;
  }

  return 0;
}

