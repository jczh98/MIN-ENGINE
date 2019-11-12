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

#include <vector>
#include "layer.h"

namespace min::engine {

class LayerStack {
 public:
  LayerStack();
  ~LayerStack();
  void PushLayer(const std::shared_ptr<Layer>& layer);
  void PushOverlay(const std::shared_ptr<Layer>& overlay);
  void PopLayer(const std::shared_ptr<Layer>& layer);
  void PopOverlay(const std::shared_ptr<Layer>& overlay);
  std::vector<std::shared_ptr<Layer>>::iterator begin() { return layers_.begin(); }
  std::vector<std::shared_ptr<Layer>>::iterator end() { return layers_.end(); }
 private:
  std::vector<std::shared_ptr<Layer>> layers_;
  uint insert_index_ = 0;
};

}
