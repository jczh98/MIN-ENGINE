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

#pragma once

#include "common.h"

namespace min::engine {

enum class ShaderDataType {
  None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
};

static uint ShaderDataTypeSize(ShaderDataType type) {
  switch (type) {
    case ShaderDataType::Float: return 4;
    case ShaderDataType::Float2: return 4 * 2;
    case ShaderDataType::Float3: return sizeof(float) * 3;
    case ShaderDataType::Float4: return 4 * 4;
    case ShaderDataType::Mat3: return 4 * 3 * 3;
    case ShaderDataType::Mat4: return 4 * 4 * 4;
    case ShaderDataType::Int: return 4;
    case ShaderDataType::Int2: return 4 * 2;
    case ShaderDataType::Int3: return 4 * 3;
    case ShaderDataType::Int4: return 4 * 4;
    case ShaderDataType::Bool: return 1;
  }
  log::Log("Unknown ShaderDataType");
  return 0;
}

struct BufferElement {
  std::string name;
  ShaderDataType type;
  uint size;
  size_t offset;
  bool normalized;

  BufferElement() = default;

  BufferElement(ShaderDataType type, const std::string &name, bool normalized = false)
      : name(name),
        type(type),
        size(ShaderDataTypeSize(type)),
        offset(0),
        normalized(normalized) {}

  uint GetComponentCount() const {
    switch (type) {
      case ShaderDataType::Float: return 1;
      case ShaderDataType::Float2: return 2;
      case ShaderDataType::Float3: return 3;
      case ShaderDataType::Float4: return 4;
      case ShaderDataType::Mat3: return 3 * 3;
      case ShaderDataType::Mat4: return 4 * 4;
      case ShaderDataType::Int: return 1;
      case ShaderDataType::Int2: return 2;
      case ShaderDataType::Int3: return 3;
      case ShaderDataType::Int4: return 4;
      case ShaderDataType::Bool: return 1;
    }
    log::Log("Unknown ShaderDataType");
    return 0;
  }
};

class BufferLayout {
 public:
  BufferLayout() {}
  BufferLayout(const std::initializer_list<BufferElement> &elements) : elements(elements) {
    CalculateOffsetAndStride();
  }
  std::vector<BufferElement>::iterator begin() { return elements.begin(); }
  std::vector<BufferElement>::iterator end() { return elements.end(); }
  std::vector<BufferElement>::const_iterator begin() const { return elements.begin(); }
  std::vector<BufferElement>::const_iterator end() const { return elements.end(); }

  std::vector<BufferElement> elements;
  uint stride = 0;
 private:
  void CalculateOffsetAndStride() {
    size_t offset = 0;
    stride = 0;
    for (auto &element : elements) {
      element.offset = offset;
      offset += element.size;
      stride += element.size;
    }
  }
};

class GLVertexBuffer {
 public:
  GLVertexBuffer(float *vertices, uint size);
  virtual ~GLVertexBuffer();
  virtual void Bind() const;
  virtual void Unbind() const;
  virtual const BufferLayout &GetLayout() const { return layout_; }
  virtual void SetLayout(const BufferLayout &layout) { layout_ = layout; }
 private:
  uint vbo_;
  BufferLayout layout_;
};

class GLIndexBuffer {
 public:
  GLIndexBuffer(uint *indices, uint count);
  virtual ~GLIndexBuffer();
  virtual void Bind() const;
  virtual void Unbind() const;
  virtual uint GetCount() const { return count_; }
 private:
  uint ebo_;
  uint count_;
};

}
