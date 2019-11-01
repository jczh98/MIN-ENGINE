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

#include <min/engine/renderer/renderer.h>
#include <min/engine/renderer/render_command.h>
#include <min/engine/renderer/renderer2d.h>
#include <min/engine/renderer/opengl/gl_shader.h>

namespace min::engine {

std::unique_ptr<Renderer::SceneData> Renderer::scene_data_ = std::make_unique<SceneData>();

void Renderer::Init() {
  RenderCommand::Init();
  Renderer2D::Init();
}

void Renderer::OnWindowResize(uint width, uint height) {
  RenderCommand::SetViewPort(0, 0, width, height);
}
void Renderer::BeginScene(Camera &camera) {
  scene_data_->view_projection = camera.view_projection;
}
void Renderer::EndScene() {

}
void Renderer::Submit(const std::shared_ptr<Shader> &shader,
                      const std::shared_ptr<VertexArray> &vertex_array,
                      Eigen::Affine3f transform) {
  shader->Bind();
  std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", scene_data_->view_projection);
  std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform.matrix());
  vertex_array->Bind();
  RenderCommand::DrawIndexed(vertex_array);
}

}
