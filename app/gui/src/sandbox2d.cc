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

#include <min/engine/renderer/render_command.h>
#include <min/engine/renderer/renderer2d.h>
#include <imgui.h>
#include "sandbox2d.h"

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), camera_controller_(1280.0f/720.0f) {

}
void Sandbox2D::OnAttach() {
  Layer::OnAttach();
}
void Sandbox2D::OnDetach() {
  Layer::OnDetach();
}
void Sandbox2D::OnUpdate(min::engine::TimeStep ts) {
  camera_controller_.OnUpdate(ts);
  using namespace min;
  using namespace min::engine;
  min::Vector4f color(.1f, 0.1f, 0.1f, 0.1f);
  RenderCommand::SetClearColor(Vector4f(0.1f, 0.1f, 0.1f, 0.1f));
  RenderCommand::Clear();
  Renderer2D::BeginScene(camera_controller_.camera);
  Renderer2D::DrawQuad(Vector2f(0.0f, 0.0f), Vector2f(1.0f, 1.0f), Vector4f(0.8f, 0.2f, 0.3f, 1.0f));
  Renderer2D::EndScene();
}
void Sandbox2D::OnImGuiRender() {
  ImGui::Begin("Settings");
  ImGui::ColorEdit4("Square Color", square_color.data());
  ImGui::End();
}
void Sandbox2D::OnEvent(min::engine::Event &e) {
  camera_controller_.OnEvent(e);
}
