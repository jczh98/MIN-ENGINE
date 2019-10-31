/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#include <min/engine/renderer/vertex_array.h>
#include <min/engine/renderer/opengl/gl_vertex_array.h>
#include <min/engine/renderer/renderer.h>

namespace min::engine {

std::shared_ptr<VertexArray> VertexArray::Create() {
  switch (Renderer::GetAPI()) {
    case RendererAPI::API::None: MIN_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
    case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexArray>();
  }
  MIN_CORE_ASSERT(false, "Unknown RendererAPI!");
  return nullptr;
}

}
