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
#include "renderer.h"

namespace min::engine {

Renderer::Renderer() {

}
Renderer::~Renderer() {

}
bool Renderer::Initialize() {
  log::Log("Initializing renderer.");
  show_demo_ = false;
  if (!InitFBOs()) {
    log::Log("FBOs' failed to be initialized correctly.");
    return false;
  }
  if (!LoadShaders()) {
    log::Log("Shaders' failed to be initialized correctly.");
    return false;
  }
  if (!PreProcess()) {
    log::Log("Failed to preprocess.");
    return false;
  }
  log::Log("Renderer initialized.");
  return true;
}
void Renderer::Shutdown() {

}
void Renderer::Render() {
  //Making sure depth testing is enabled
  glEnable(GL_DEPTH_TEST);
  glDepthMask(true);
}
bool Renderer::InitFBOs() {
  return true;
}
bool Renderer::LoadShaders() {
  return true;
}
bool Renderer::PreProcess() {
  return true;
}
void Renderer::PostProcess() {

}
void Renderer::OnGUI() {
  if (show_demo_) {
    ImGui::ShowDemoWindow(&show_demo_);
  }
  ImGui::Begin("Hello world!");
  ImGui::Checkbox("Demo", &show_demo_);
  ImGui::End();
}

}