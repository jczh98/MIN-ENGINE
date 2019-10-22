/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */

#include <min/engine/core/application.h>
#include <min/engine/renderer/renderer.h>

MIN_ENGINE_NAMESPACE_BEGIN

Application* Application::instance_ = nullptr;

Application::Application() {
  if (instance_ !=nullptr) {
    return;
  }
  instance_ = this;
  window = std::make_unique<Window>(Window::Create());
  window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

  Renderer::Init();

  imgui_layer = new ImGuiLayer();
  PushOverlay(imgui_layer);
}
void Application::OnEvent(Event &e) {
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
  dispatcher.Dispatch<WindowResizeEvent>(std::bind(&Application::OnWindowResize, this, std::placeholders::_1));
  for (auto it = layer_stack_.end(); it!=layer_stack_.begin();) {
    (*--it)->OnEvent((e));
    if (e.handled) break;
  }
}
void Application::Run() {
  while (running_) {
    if (!minimized_) {
      for (auto layer : layer_stack_) {
        layer->OnUpdate();
      }
      imgui_layer->Begin();
      for (auto layer : layer_stack_) {
        layer->OnImGuiRender();
      }
      imgui_layer->End();
      window->OnUpdate();
    }
  }
}
void Application::PushLayer(Layer *layer) {
  layer_stack_.PushLayer(layer);
}
void Application::PushOverlay(Layer *layer) {
  layer_stack_.PushOverlay(layer);
}
bool Application::OnWindowClose(WindowCloseEvent &e) {
  running_ = false;
  return true;
}
bool Application::OnWindowResize(WindowResizeEvent &e) {
  if (e.width == 0 || e.height == 0) {
    minimized_ = true;
    return false;
  }
  minimized_ = false;
  Renderer::OnWindowResize(e.width, e.height);
  return false;
}
MIN_ENGINE_NAMESPACE_END
