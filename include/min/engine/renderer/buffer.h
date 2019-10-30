/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include <min/engine/core/core.h>

MIN_ENGINE_NAMESPACE_BEGIN

enum class ShaderDataType {
  None = 0,
  Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
};

static uint ShaderDataTypeSize(ShaderDataType type) {
  switch (type) {
    case ShaderDataType::Float: return 4;
    case ShaderDataType::Float2: return 4*2;
    case ShaderDataType::Float3: return 4*3;
    case ShaderDataType::Float4: return 4*4;
    case ShaderDataType::Mat3: return 4*3*3;
    case ShaderDataType::Mat4: return 4*4*4;
    case ShaderDataType::Int: return 4;
    case ShaderDataType::Int2: return 4*2;
    case ShaderDataType::Int3: return 4*3;
    case ShaderDataType::Int4: return 4*4;
    case ShaderDataType::Bool: return 1;
  }
  MIN_CORE_ASSERT(false, "Unknown ShaderDataType!");
}

struct BufferElement {
  std::string name;
  ShaderDataType type;
  uint size;
  size_t offset;
  bool normalized;

  BufferElement() = default;

  BufferElement(ShaderDataType type, const std::string &name, bool normalized = false) : name(name),
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
      case ShaderDataType::Mat3: return 3*3;
      case ShaderDataType::Mat4: return 4*4;
      case ShaderDataType::Int: return 1;
      case ShaderDataType::Int2: return 2;
      case ShaderDataType::Int3: return 3;
      case ShaderDataType::Int4: return 4;
      case ShaderDataType::Bool: return 1;
    }
    MIN_CORE_ASSERT(false, "Unknown ShaderDataType!");
    return 0;
  }
};

class BufferLayout {
 public:
  BufferLayout(const std::initializer_list<BufferElement>& elements) : elements(elements) {
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
    for (auto& element : elements) {
      element.offset = offset;
      offset += element.size;
      stride += element.size;
    }
  }
};

class VertexBuffer {
 public:
  virtual ~VertexBuffer() = default;
  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;
  virtual const BufferLayout& GetLayout() const = 0;
  virtual void SetLayout(const BufferLayout& layout) = 0;
  static VertexBuffer* Create(float* vertices, uint size);
};

class IndexBuffer {
 public:
  virtual ~IndexBuffer() = default;
  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;
  virtual uint GetCount() const = 0;
  static IndexBuffer* Create(uint* indices, uint size);
};

MIN_ENGINE_NAMESPACE_END

