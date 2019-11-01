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

#include <min/engine/core/layer.h>
#include <min/engine/core/timestep.h>
#include <min/engine/renderer/camera_controller.h>
#include <min/engine/renderer/vertex_array.h>
#include <min/engine/renderer/shader.h>

class Sandbox2D : public min::engine::Layer {
  public:
  Sandbox2D();
  virtual ~Sandbox2D() = default;
  virtual void OnAttach() override ;
  virtual void OnDetach() override ;
  void OnUpdate(min::engine::TimeStep ts) override;
  virtual void OnImGuiRender() override ;
  void OnEvent(min::engine::Event& e) override ;
  private:
  min::engine::CameraController camera_controller_;
  std::shared_ptr<min::engine::VertexArray> square_va;
  std::shared_ptr<min::engine::Shader> flat_color_shader;

  min::Vector4f square_color = {0.2f, 0.3f, 0.8f, 1.0f};
};
