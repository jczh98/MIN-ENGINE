/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include <min/engine/core/core.h>
#include "buffer.h"

namespace min::engine {

class VertexArray {
 public:
  virtual ~VertexArray() {}
  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;
  virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertex_buffer) = 0;
  virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& index_buffer) = 0;
  virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
  virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

  static std::shared_ptr<VertexArray> Create();
};

}

