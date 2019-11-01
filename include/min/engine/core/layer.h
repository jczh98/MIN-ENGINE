/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include "core.h"
#include "engine/events/event.h"
#include "timestep.h"

namespace min {
namespace engine {

class Layer {
 public:
  Layer(const std::string& name = "Layer") : name(name) {}
  virtual ~Layer() = default;
  virtual void OnAttach() {}
  virtual void OnDetach() {}
  virtual void OnUpdate(TimeStep ts) {}
  virtual void OnImGuiRender() {}
  virtual void OnEvent(Event& event) {}
  std::string name;
};

}
}
