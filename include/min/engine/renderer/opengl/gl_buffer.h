/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include <GL/glew.h>
#include "../buffer.h"

MIN_ENGINE_NAMESPACE_BEGIN


class OpenGLVertexBuffer : public VertexBuffer {
 public:
  OpenGLVertexBuffer(float* vertices, uint size);
  virtual ~OpenGLVertexBuffer();
  virtual void Bind() const override ;
  virtual void Unbind() const override ;
  virtual const BufferLayout &GetLayout() const override { return layout_; }
  virtual void SetLayout(const BufferLayout &layout) override { layout_ = layout; }
 private:
  uint id_;
  BufferLayout layout_;
};

class OpenGLIndexBuffer : public IndexBuffer {
 public:
  OpenGLIndexBuffer(uint* indices, uint count);
  virtual ~OpenGLIndexBuffer();
  virtual void Bind() const override;
  virtual void Unbind() const override;
  virtual uint GetCount() const { return count_; }
 private:
  uint id_;
  uint count_;
};


MIN_ENGINE_NAMESPACE_END
