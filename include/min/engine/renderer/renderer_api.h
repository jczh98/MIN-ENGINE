/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include <min/engine/core/core.h>
#include "vertex_array.h"

MIN_ENGINE_NAMESPACE_BEGIN

class RendererAPI {
 public:
  enum class API {
    None = 0, OpenGL = 1
  };
  virtual void Init() = 0;
  virtual void SetViewport(uint x, uint y, uint width, uint height) = 0;
  virtual void SetClearColor(const Vector4f color) = 0;
  virtual void Clear() = 0;

  virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertex_array) = 0;
  inline static API GetAPI() { return API_; }
 private:
  static API API_;
};

RendererAPI::API API_ = RendererAPI::API::OpenGL;



MIN_ENGINE_NAMESPACE_END
