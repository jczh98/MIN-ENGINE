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

#include "renderer_api.h"

namespace min::engine {

class RenderCommand {
 public:
  inline static Init();
  inline static void SetViewPort(uint x, uint y, uint width, uint height) {
    renderer_api_->SetViewport(x, y, width, height);
  }
  inline static void SetClearColor(Vector4f& color) {
    renderer_api->SetClearColor(color);
  }
  inline static void Clear() {
    renderer_api_->Clear();
  }
  inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertex_array) {
    renderer_api_->DrawIndexed(vertex_array);
  }
 private:
  static std::unique_ptr<RendererAPI> renderer_api_;
};
}
