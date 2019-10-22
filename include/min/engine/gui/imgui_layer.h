/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include <min/engine/core/layer.h>

namespace min {
namespace engine {

class ImGuiLayer : public Layer {
 public:
  ImGuiLayer();
  ~ImGuiLayer() = default;
  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnImGuiRender() override;

  void Begin();
  void End();
};


}
}
