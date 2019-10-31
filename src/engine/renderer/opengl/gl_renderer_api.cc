/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#include <min/engine/renderer/opengl/gl_renderer_api.h>
#include <GL/glew.h>

namespace min::engine {

void OpenGLRendererAPI::Init() {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void OpenGLRendererAPI::SetViewport(uint x, uint y, uint width, uint height) {
  glViewport(x, y, width, height);
}
void OpenGLRendererAPI::SetClearColor(const Vector4f color) {
  glClearColor(color.x(), color.y(), color.z(), color.w());
}
void OpenGLRendererAPI::Clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray> &vertex_array) {
  glDrawElements(GL_TRIANGLES, vertex_array->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}

}
