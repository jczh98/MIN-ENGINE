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

#include "application.h"

namespace min::engine {

Application* Application::instance_ = nullptr;

Application::Application() {
  if (instance_ !=nullptr) {
    return;
  }
  instance_ = this;
  window_ = Window::Create();
  window_->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

  //Renderer::Init();

  imgui_layer_ = std::make_shared<ImGuiLayer>();
  PushOverlay(imgui_layer_);
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
    auto time = (float) glfwGetTime();
    TimeStep ts = time - last_frame_time_;
    last_frame_time_ = time;
    if (!minimized_) {
      for (const auto& layer : layer_stack_) {
        layer->OnUpdate(ts);
      }
    }
    imgui_layer_->Begin();
    for (const auto& layer : layer_stack_) {
      layer->OnImGuiRender();
    }
    imgui_layer_->End();
    window_->OnUpdate();
  }
}
void Application::PushLayer(const std::shared_ptr<Layer>& layer) {
  layer_stack_.PushLayer(layer);
}
void Application::PushOverlay(const std::shared_ptr<Layer>& layer) {
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
  //Renderer::OnWindowResize(e.width, e.height);
  return false;
}

}
