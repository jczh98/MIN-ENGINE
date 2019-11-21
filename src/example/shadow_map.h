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
  ShadowMap() : controller_(1280.0f/720.0f) {
    shader_ =
        std::make_shared<GLShader>("assets/shaders/shadow_map/shadow_map.vs.glsl",
                                   "assets/shaders/shadow_map/shadow_map.fs.glsl");
    depth_shader_ = std::make_shared<GLShader>("assets/shaders/shadow_map/shadow_map_depth.vs.glsl",
                                               "assets/shaders/shadow_map/shadow_map_depth.fs.glsl");
    depth_quad_ =
        std::make_shared<GLShader>("assets/shaders/shadow_map/debug_quad.vs.glsl",
                                   "assets/shaders/shadow_map/debug_quad.fs.glsl");
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
    glGenFramebuffers(1, &depth_map_fbo_);
    glGenTextures(1, &depth_map_);
    glBindTexture(GL_TEXTURE_2D, depth_map_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT,
                 nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float border_color[] = {1.0, 1.0, 1.0, 1.0};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);

    glBindFramebuffer(GL_FRAMEBUFFER, depth_map_fbo_);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_map_, 0);
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
    vao_->Unbind();
    plane_->Unbind();
  }

  // renderCube() renders a 1x1 3D cube in NDC.
  // -------------------------------------------------
  unsigned int cubeVAO = 0;
  unsigned int cubeVBO = 0;
  void RenderCube() {
    // initialize (if necessary)
    if (cubeVAO == 0) {
      float vertices[] = {
          // back face
          -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
          1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // top-right
          1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, // bottom-right
          1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // top-right
          -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
          -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, // top-left
          // front face
          -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
          1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // bottom-right
          1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // top-right
          1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // top-right
          -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // top-left
          -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
          // left face
          -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
          -1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-left
          -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
          -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
          -1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom-right
          -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
          // right face
          1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-left
          1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-right
          1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-right
          1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-right
          1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-left
          1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom-left
          // bottom face
          -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
          1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, // top-left
          1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom-left
          1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom-left
          -1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom-right
          -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
          // top face
          -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top-left
          1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
          1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top-right
          1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
          -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top-left
          -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f  // bottom-left
      };
      glGenVertexArrays(1, &cubeVAO);
      glGenBuffers(1, &cubeVBO);
      // fill buffer
      glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
      // link vertex attributes
      glBindVertexArray(cubeVAO);
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
      glEnableVertexAttribArray(2);
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0);
    }
    // render Cube
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
  }

  // renderQuad() renders a 1x1 XY quad in NDC
  // -----------------------------------------
  unsigned int quadVAO = 0;
  unsigned int quadVBO;
  void RenderQuad() {
    if (quadVAO == 0) {
      float quadVertices[] = {
          // positions        // texture Coords
          -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
          -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
          1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
          1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
      };
      // setup plane VAO
      glGenVertexArrays(1, &quadVAO);
      glGenBuffers(1, &quadVBO);
      glBindVertexArray(quadVAO);
      glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
      glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    }
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
  }

  void RenderScene(const std::shared_ptr<GLShader> &shader) {
    // floor
    Matrix4f model = Matrix4f::Identity();
    shader->UploadUniformMat4("model", model);
    vao_->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // cubes
    Eigen::Affine3f trans = Eigen::Affine3f::Identity();
    trans.translate(Vector3f(0.0f, 1.5f, 0.0f));
    trans.scale(Vector3f(0.5f, 0.5f, 0.5f));
    shader->UploadUniformMat4("model", trans.matrix());
    RenderCube();
    trans = Eigen::Affine3f::Identity();
    trans.translate(Vector3f(2.0f, 0.0f, 1.0f));
    trans.scale(Vector3f(0.5f, 0.5f, 0.5f));
    shader->UploadUniformMat4("model", trans.matrix());
    RenderCube();
    trans = Eigen::Affine3f::Identity();
    trans.translate(Vector3f(-1.0f, 0.0f, 2.0f));
    Eigen::AngleAxisf rotation(nf::math::radians(60.0f), Vector3f(1.0f, 0.0f, 1.0f));
    trans.rotate(rotation);
    trans.scale(Vector3f(0.25f, 0.25f, 0.25f));
    shader->UploadUniformMat4("model", trans.matrix());
    RenderCube();
  }

  void OnUpdate(TimeStep ts) override {
    controller_.OnUpdate(ts);

    Vector3f light_pos(-2.0f, 4.0f, -1.0f);

    Renderer::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Renderer::Clear();

    Matrix4f light_projection, light_view;
    Matrix4f light_space;
    float z_near = 1.0f, z_far = 7.5f;
    light_projection = nf::math::Ortho(-10.0f, 10.0f, -10.0f, 10.0f, z_near, z_far);
    light_view = nf::math::LookAt(light_pos, Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
    light_space = light_projection * light_view;

    depth_shader_->Use();
    depth_shader_->UploadUniformMat4("lightSpaceMatrix", light_space);

    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depth_map_fbo_);
    glClear(GL_DEPTH_BUFFER_BIT);
    wood_->Bind(GL_TEXTURE0);
    RenderScene(depth_shader_);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // reset viewport
    glViewport(0, 0, Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader_->Use();
    Matrix4f projection = controller_.camera.GetProjectionMatrix();
    Matrix4f view = controller_.camera.GetViewMatrix();
    shader_->UploadUniformMat4("projection", projection);
    shader_->UploadUniformMat4("view", view);
    // Set light
    shader_->UploadUniformFloat3("viewPos", controller_.camera.position());
    shader_->UploadUniformFloat3("lightPos", light_pos);
    shader_->UploadUniformMat4("lightSpaceMatrix", light_space);
    wood_->Bind(GL_TEXTURE0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, depth_map_);
    RenderScene(shader_);

    // Render depth map to quad for visual debugging
    depth_quad_->Use();
    depth_quad_->UploadUniformFloat("near_plane", z_near);
    depth_quad_->UploadUniformFloat("far_plane", z_far);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, depth_map_);
    //RenderQuad();
  }

  void OnImGuiRender() override {
  }

  void OnEvent(Event &event) override {
    controller_.OnEvent(event);
  }

  const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
 private:
  uint depth_map_fbo_;
  uint depth_map_;
  std::shared_ptr<GLShader> shader_, depth_shader_, depth_quad_;
  std::shared_ptr<GLVertexArray> vao_;
  std::shared_ptr<GLVertexBuffer> plane_;
  std::shared_ptr<GLTexture> wood_;
  Controller controller_;
};
