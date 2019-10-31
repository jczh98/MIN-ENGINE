/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#include <min/engine/renderer/opengl/gl_vertex_array.h>
#include <GL/glew.h>

namespace min::engine {
static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
  switch (type) {
    case min::engine::ShaderDataType::Float: return GL_FLOAT;
    case min::engine::ShaderDataType::Float2: return GL_FLOAT;
    case min::engine::ShaderDataType::Float3: return GL_FLOAT;
    case min::engine::ShaderDataType::Float4: return GL_FLOAT;
    case min::engine::ShaderDataType::Mat3: return GL_FLOAT;
    case min::engine::ShaderDataType::Mat4: return GL_FLOAT;
    case min::engine::ShaderDataType::Int: return GL_INT;
    case min::engine::ShaderDataType::Int2: return GL_INT;
    case min::engine::ShaderDataType::Int3: return GL_INT;
    case min::engine::ShaderDataType::Int4: return GL_INT;
    case min::engine::ShaderDataType::Bool: return GL_BOOL;
  }
  MIN_CORE_ERROR("Unknown ShaderDataType!");
  return 0;
}
OpenGLVertexArray::OpenGLVertexArray() {
  glCreateVertexArrays(1, &id_);
}
OpenGLVertexArray::~OpenGLVertexArray() {
  glDeleteVertexArrays(1, &id_);
}
void OpenGLVertexArray::Bind() const {
  glBindVertexArray(id_);
}
void OpenGLVertexArray::Unbind() const {
  glBindVertexArray(0);
}
void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertex_buffer) {
  MIN_CORE_ASSERT(vertex_buffer->GetLayout().elements.size(), "Vertex Buffer has no layout!");
  glBindVertexArray(id_);
  vertex_buffer->Bind();
  const auto &layout = vertex_buffer->GetLayout();
  for (const auto &element : layout) {
    glEnableVertexAttribArray(vertex_buffer_index_);
    glVertexAttribPointer(vertex_buffer_index_,
                          element.GetComponentCount(),
                          ShaderDataTypeToOpenGLBaseType(element.type),
                          element.normalized ? GL_TRUE : GL_FALSE,
                          layout.stride,
                          (const void *) element.offset);
    vertex_buffer_index_++;
  }
  vertex_buffers_.emplace_back(vertex_buffer);
}
void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> &index_buffer) {
  glBindVertexArray(id_);
  index_buffer->Bind();
  index_buffer_ = index_buffer;
}

}
