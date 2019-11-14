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
#include "gl_buffer.h"

namespace min::engine {

class GLVertexArray {

 public:
  GLVertexArray();
  virtual ~GLVertexArray();
  virtual void Bind() const;
  virtual void Unbind() const;
  void AddVertexBuffer(const std::shared_ptr<GLVertexBuffer>& vertex_buffer);
  void SetIndexBuffer(const std::shared_ptr<GLIndexBuffer>& index_buffer);
 private:
  uint vao_;
  uint vertex_buffer_index_;
  std::vector<std::shared_ptr<GLVertexBuffer>> vertex_buffers_;
  std::shared_ptr<GLIndexBuffer> index_buffer_;
};

}
