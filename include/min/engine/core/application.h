/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include "core.h"
#include "window.h"
#include "layer.h"
#include "layer_stack.h"
#include "../events/event.h"
#include "../events/application_event.h"
#include "../gui/imgui_layer.h"

MIN_ENGINE_NAMESPACE_BEGIN

class Application {
 public:
  Application();
  virtual ~Application() = default;
  void Run();
  void OnEvent(Event& e);

  void PushLayer(Layer* layer);
  void PushOverlay(Layer* layer);

  inline static Application& Get() { return *instance_; }
  std::unique_ptr<Window> window;
  ImGuiLayer* imgui_layer;
 private:
  bool OnWindowClose(WindowCloseEvent& e);
  bool OnWindowResize(WindowResizeEvent& e);

  bool running_ = true;
  bool minimized_ = false;
  LayerStack layer_stack_;
  static Application* instance_;
};

MIN_ENGINE_NAMESPACE_END
