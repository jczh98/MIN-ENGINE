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

#include "common.h"
#include "events/application_event.h"
#include "window.h"
#include "layer_stack.h"
#include "imgui_layer.h"
namespace min::engine {

class Application {
 public:
  Application();
  virtual ~Application() = default;
  void Run();
  void OnEvent(Event& e);

  void PushLayer(std::shared_ptr<Layer> layer);
  void PushOverlay(std::shared_ptr<Layer> layer);

  inline static Application& Get() { return *instance_; }
 private:
  bool OnWindowClose(WindowCloseEvent& e);
  bool OnWindowResize(WindowResizeEvent& e);

  std::shared_ptr<ImGuiLayer> imgui_layer_;
  std::unique_ptr<Window> window_;
  bool running_ = true;
  bool minimized_ = false;
  float last_frame_time = 0.0f;
  LayerStack layer_stack_;
  static Application* instance_;
};

}
