/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include <min/engine/core/core.h>
#include "renderer_api.h"
#include "camera.h"
#include "shader.h"

MIN_ENGINE_NAMESPACE_BEGIN

class Renderer {
 public:
  static void Init();
  static void OnWindowResize(uint width, uint height);
  static void BeginScene(Camera &camera);
  static void EndScene();
  static void Submit(const std::shared_ptr<Shader> &shader,
                     const std::shared_ptr<VertexArray> &vertex_array,
                     const Eigen::Affine3f transform = Eigen::Affine3f::Identity());
  inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
 private:
  struct SceneData {
    Matrix4f view_projection;
  };
  static std::unique_ptr<SceneData> scene_data_;
};

MIN_ENGINE_NAMESPACE_END

