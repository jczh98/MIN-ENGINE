// MIT License
// 
// Copyright (c) 2018-2019, neverfelly <neverfelly@gmail.com>
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "gl_vertex_array.h"

namespace min::engine {

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
  switch (type) {
    case ShaderDataType::Float: return GL_FLOAT;
    case ShaderDataType::Float2: return GL_FLOAT;
    case ShaderDataType::Float3: return GL_FLOAT;
    case ShaderDataType::Float4: return GL_FLOAT;
    case ShaderDataType::Mat3: return GL_FLOAT;
    case ShaderDataType::Mat4: return GL_FLOAT;
    case ShaderDataType::Int: return GL_INT;
    case ShaderDataType::Int2: return GL_INT;
    case ShaderDataType::Int3: return GL_INT;
    case ShaderDataType::Int4: return GL_INT;
    case ShaderDataType::Bool: return GL_BOOL;
  }
  log::Log("Unknown ShaderDataType!");
  return 0;
}

GLVertexArray::GLVertexArray() {
  glGenVertexArrays(1, &vao_);
}
GLVertexArray::~GLVertexArray() {
  glDeleteVertexArrays(1, &vao_);
}
void GLVertexArray::Bind() const {
  glBindVertexArray(vao_);
}
void GLVertexArray::Unbind() const {
  glBindVertexArray(0);
}
void GLVertexArray::AddVertexBuffer(const std::shared_ptr<GLVertexBuffer> &vertex_buffer) {
  if (vertex_buffer->GetLayout().elements.empty()) {
    log::Log("VertexBuffer has no layout.");
    return;
  }
  glBindVertexArray(vao_);
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
  vertex_buffers.emplace_back(vertex_buffer);
}
void GLVertexArray::SetIndexBuffer(const std::shared_ptr<GLIndexBuffer> &index_buffer) {
  glBindVertexArray(vao_);
  index_buffer->Bind();
  this->index_buffer = index_buffer;
}

}