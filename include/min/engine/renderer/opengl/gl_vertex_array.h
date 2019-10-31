/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include "../vertex_array.h"

namespace min::engine {

class OpenGLVertexArray : public VertexArray {
 public:
  OpenGLVertexArray();
  virtual ~OpenGLVertexArray();
  virtual void Bind() const override ;
  virtual void Unbind() const override;

  void AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertex_buffer) override;
  void SetIndexBuffer(const std::shared_ptr<IndexBuffer> &index_buffer) override;
  const std::vector<std::shared_ptr<VertexBuffer>> &GetVertexBuffers() const override { return vertex_buffers_; }
  const std::shared_ptr<IndexBuffer> &GetIndexBuffer() const override { return index_buffer_; }
 private:
  uint id_;
  uint vertex_buffer_index_;
  std::vector<std::shared_ptr<VertexBuffer>> vertex_buffers_;
  std::shared_ptr<IndexBuffer> index_buffer_;
};

}

