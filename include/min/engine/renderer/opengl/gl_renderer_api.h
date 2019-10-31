/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include "../renderer_api.h"

namespace min::engine {

class OpenGLRendererAPI : public RendererAPI {
 public:
  virtual void Init() override;
  virtual void SetViewport(uint x, uint y, uint width, uint height) override;
  virtual void SetClearColor(const Vector4f color) override;
  virtual void Clear() override;
  virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertex_array) override;
};

}

