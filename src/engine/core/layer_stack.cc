/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#include <min/engine/core/layer_stack.h>

MIN_ENGINE_NAMESPACE_BEGIN

LayerStack::LayerStack() {
}

LayerStack::~LayerStack() {
  for (Layer *layer : layers_) {
    layer->OnDetach();
    delete layer;
  }
}

void LayerStack::PushLayer(Layer *layer) {
  layers_.emplace(layers_.begin() + insert_index_, layer);
  insert_index_++;
  layer->OnAttach();
}

void LayerStack::PushOverlay(Layer *overlay) {
  layers_.emplace_back(overlay);
  overlay->OnAttach();
}

void LayerStack::PopLayer(Layer *layer) {
  auto it = std::find(layers_.begin(), layers_.begin() + insert_index_, layer);
  if (it!=layers_.begin() + insert_index_) {
    layer->OnDetach();
    layers_.erase(it);
    insert_index_--;
  }
}

void LayerStack::PopOverlay(Layer *overlay) {
  auto it = std::find(layers_.begin() + insert_index_, layers_.end(), overlay);
  if (it!=layers_.end()) {
    overlay->OnDetach();
    layers_.erase(it);
  }
}

MIN_ENGINE_NAMESPACE_END
