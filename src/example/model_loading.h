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

#include "../application.h"
#include "../gl_shader.h"
#include "../controller.h"
#include "../model.h"

using namespace min::engine;

class ModelLoadingLayer : public Layer {
 public:
  ModelLoadingLayer() {
    controller_ = std::make_unique<Controller>(1280.0f / 720.0f);
  }
  void OnAttach() override {
    shader_ = std::make_shared<GLShader>("assets/shaders/model.vs.glsl", "assets/shaders/model.fs.glsl");
    model_ = std::make_unique<Model>("assets/objs/nanosuit/nanosuit.obj");
  }
  void OnEvent(Event &e) override {
    controller_->OnEvent(e);
  }
  void OnUpdate(TimeStep ts) override {
    controller_->OnUpdate(ts);
    Renderer::SetClearColor({0.1, 0.1, 0.1, 1});
    Renderer::Clear();
    shader_->Use();
    Matrix4f projection = controller_->camera.GetProjectionMatrix();
    Matrix4f view = controller_->camera.GetViewMatrix();
    shader_->UploadUniformMat4("projection", projection);
    shader_->UploadUniformMat4("view", view);
    // render the loaded model
    Eigen::Affine3f t = Eigen::Affine3f::Identity();
    t.translate(Vector3f(0.0f, -1.75f, 0.0f));
    t.scale(0.2f);
    shader_->UploadUniformMat4("model", t.matrix());
    model_->Draw(shader_);
  }

  void OnDetach() override {

  }

  void OnImGuiRender() override {

  }

 private:
  std::unique_ptr<Controller> controller_;
  std::unique_ptr<Model> model_;
  std::shared_ptr<GLShader> shader_;
};
