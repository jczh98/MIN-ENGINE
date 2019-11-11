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

#include "layer_stack.h"

namespace min::engine {

LayerStack::LayerStack() {
}

LayerStack::~LayerStack() {
  for (Layer *layer : layers_) {
    layer->OnDetach();
    delete layer;
  }
}

void LayerStack::PushLayer(std::shared_ptr<Layer> layer) {
  layers_.emplace(layers_.begin() + insert_index_, layer);
  insert_index_++;
  layer->OnAttach();
}

void LayerStack::PushOverlay(std::shared_ptr<Layer> overlay) {
  layers_.emplace_back(overlay);
  overlay->OnAttach();
}

void LayerStack::PopLayer(std::shared_ptr<Layer> layer) {
  auto it = std::find(layers_.begin(), layers_.begin() + insert_index_, layer);
  if (it!=layers_.begin() + insert_index_) {
    layer->OnDetach();
    layers_.erase(it);
    insert_index_--;
  }
}

void LayerStack::PopOverlay(std::shared_ptr<Layer> overlay) {
  auto it = std::find(layers_.begin() + insert_index_, layers_.end(), overlay);
  if (it!=layers_.end()) {
    overlay->OnDetach();
    layers_.erase(it);
  }
}

}
