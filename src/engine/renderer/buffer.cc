/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#include <min/engine/renderer/buffer.h>
#include <min/engine/renderer/renderer.h>
#include <min/engine/renderer/opengl/gl_buffer.h>

namespace min::engine {

IndexBuffer *IndexBuffer::Create(uint *indices, uint size) {
  switch (RendererAPI::GetAPI()) {
    case RendererAPI::API::None: MIN_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
    case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, size);
  }
  MIN_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

VertexBuffer *VertexBuffer::Create(float *vertices, uint size) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None: MIN_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
    case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
  }
  MIN_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}
}
