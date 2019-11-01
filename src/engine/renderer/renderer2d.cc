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

#include <min/engine/renderer/renderer2d.h>
#include <min/engine/renderer/vertex_array.h>
#include <min/engine/renderer/shader.h>
#include <min/engine/renderer/opengl/gl_shader.h>
#include <min/engine/renderer/render_command.h>

namespace min::engine {

struct Renderer2DStorage {
  std::shared_ptr<VertexArray> quad_vertex_array;
  std::shared_ptr<Shader> flat_color_shader;
};

static Renderer2DStorage *data;

void Renderer2D::Init() {
  data = new Renderer2DStorage();
  data->quad_vertex_array = VertexArray::Create();
  float square_vertices[5*4] = {
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.5f, 0.5f, 0.0f,
      -0.5f, 0.5f, 0.0f
  };
  std::shared_ptr<VertexBuffer> square_vb;
  square_vb.reset(VertexBuffer::Create(square_vertices, sizeof(square_vertices)));
  square_vb->SetLayout({
                           {ShaderDataType::Float3, "a_Position"}
                       });
  data->quad_vertex_array->AddVertexBuffer(square_vb);
  uint square_indices[6] = {0, 1, 2, 2, 3, 0};
  std::shared_ptr<IndexBuffer> square_ib =
      std::make_shared<IndexBuffer>(IndexBuffer::Create(square_indices, sizeof(square_indices)/sizeof(uint)));
  data->quad_vertex_array->SetIndexBuffer(square_ib);
  data->flat_color_shader =
      Shader::Create("assets/shaders/flat_color.vert.glsl", "assets/shaders/flat_color.frag.glsl");
}
void Renderer2D::Shutdown() {
  delete (data);
}
void Renderer2D::BeginScene(const Camera &camera) {
  std::dynamic_pointer_cast<OpenGLShader>(data->flat_color_shader)->Bind();
  std::dynamic_pointer_cast<OpenGLShader>(data->flat_color_shader)
      ->UploadUniformMat4("u_ViewProjection", camera.view_projection);
  std::dynamic_pointer_cast<OpenGLShader>(data->flat_color_shader)
      ->UploadUniformMat4("u_Transform", Matrix4f::Identity());
}
void Renderer2D::EndScene() {

}
void Renderer2D::DrawQuad(const Vector2f &position, const Vector2f &size, const Vector4f &color) {
  DrawQuad(Vector3f(position.x(), position.y(), 0.0f), size, color);
}

void Renderer2D::DrawQuad(const Vector3f &position, const Vector2f &size, const Vector4f &color) {
  std::dynamic_pointer_cast<OpenGLShader>(data->flat_color_shader)->Bind();
  std::dynamic_pointer_cast<OpenGLShader>(data->flat_color_shader)->UploadUniformFloat4("u_Color", color);
  data->quad_vertex_array->Bind();
  RenderCommand::DrawIndexed(data->quad_vertex_array);
}

}
