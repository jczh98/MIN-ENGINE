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
#include "../layer.h"
#include "../controller.h"
#include "../gl_shader.h"
#include "../gl_vertex_array.h"
#include "../gl_texture.h"

using namespace min::engine;

class ShadowMap : public Layer {
 public:
  ~ShadowMap() {
    controller_ = Controller(1280.0f / 720.0f);
    shader_ =
        std::make_shared<GLShader>("assets/shaders/shadow_map/shadow_map.vs.glsl", "assets/shaders/shadow_map.fs.glsl");
    depth_shader_ = std::make_shared<GLShader>("assets/shaders/shadow_map/shadow_map_depth.vs.glsl",
                                               "assets/shaders/shadow_map.fs.glsl");
    depth_quad_ =
        std::make_shared<GLShader>("assets/shaders/shadow_map/debug_quad.vs.glsl", "assets/shaders/shadow_map.gs.glsl");
  }
  void OnAttach() override {
    glEnable(GL_DEPTH_TEST);
    std::vector<float> plane_vertices = {
        // positions            // normals         // texcoords
        25.0f, -0.5f, 25.0f, 0.0f, 1.0f, 0.0f, 25.0f, 0.0f,
        -25.0f, -0.5f, 25.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -25.0f, -0.5f, -25.0f, 0.0f, 1.0f, 0.0f, 0.0f, 25.0f,

        25.0f, -0.5f, 25.0f, 0.0f, 1.0f, 0.0f, 25.0f, 0.0f,
        -25.0f, -0.5f, -25.0f, 0.0f, 1.0f, 0.0f, 0.0f, 25.0f,
        25.0f, -0.5f, -25.0f, 0.0f, 1.0f, 0.0f, 25.0f, 25.0f
    };
    vao_ = std::make_shared<GLVertexArray>();
    plane_ = std::make_shared<GLVertexBuffer>(plane_vertices, plane_vertices.size());
    BufferLayout layout = {
        {ShaderDataType::Float3},
        {ShaderDataType::Float3},
        {ShaderDataType::Float2}
    };
    plane_->SetLayout(layout);
    vao_->AddVertexBuffer(plane_);
    wood_ = std::make_shared<GLTexture>("assets/textures/wood.png");
    // depth map FBO
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    uint depth_map_fbo;
    glGenFramebuffers(1, &depth_map_fbo);
    uint depth_map;
    glGenTextures(1, &depth_map);
    glBindTexture(GL_TEXTURE_2D, depth_map);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float border_color[] =  { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);

    glBindFramebuffer(GL_FRAMEBUFFER, depth_map_fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_map, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    shader_->Use();
    shader_->UploadUniformInt("diffuseTexture", 0);
    shader_->UploadUniformInt("shadowMap", 1);
    depth_quad_->Use();
    depth_quad_->UploadUniformInt("depthMap", 0);

  }
  void OnDetach() override {
  }
  void OnUpdate(TimeStep ts) override {
    controller_.OnUpdate(ts);
  }
  void OnImGuiRender() override {
  }
  void OnEvent(Event &event) override {
    controller_.OnEvent(event);
  }
 private:
  std::shared_ptr<GLShader> shader_, depth_shader_, depth_quad_;
  std::shared_ptr<GLVertexArray> vao_;
  std::shared_ptr<GLVertexBuffer> plane_;
  std::shared_ptr<GLTexture> wood_;
  Controller controller_;
};
