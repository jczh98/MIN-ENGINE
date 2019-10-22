/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include "core.h"
#include "layer.h"

MIN_ENGINE_NAMESPACE_BEGIN

class LayerStack {
 public:
  LayerStack();
  ~LayerStack();
  void PushLayer(Layer* layer);
  void PushOverlay(Layer* overlay);
  void PopLayer(Layer* layer);
  void PopOverlay(Layer* overlay);
  std::vector<Layer*>::iterator begin() { return layers_.begin(); }
  std::vector<Layer*>::iterator end() { return layers_.end(); }
 private:
  std::vector<Layer*> layers_;
  uint insert_index_;
};

MIN_ENGINE_NAMESPACE_END

