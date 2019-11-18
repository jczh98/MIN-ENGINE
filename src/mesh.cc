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
#include "mesh.h"

namespace min::engine {

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<uint> &indices, std::vector<Texture> &textures)
    : vertices_(vertices),
      indices_(indices),
      textures_(textures) {
  vertex_array = std::make_shared<GLVertexArray>();
  std::vector<float> datas;
  for (auto vert : vertices) {
    datas.emplace_back(vert.position.x());
    datas.emplace_back(vert.position.y());
    datas.emplace_back(vert.position.z());
    datas.emplace_back(vert.normal.x());
    datas.emplace_back(vert.normal.y());
    datas.emplace_back(vert.normal.z());
    datas.emplace_back(vert.tex_coords.x());
    datas.emplace_back(vert.tex_coords.y());
  }
  vertex_buffer = std::make_shared<GLVertexBuffer>(datas, datas.size());
  BufferLayout layout = {
      {ShaderDataType::Float3},
      {ShaderDataType::Float3},
      {ShaderDataType::Float2}
  };
  vertex_buffer->SetLayout(layout);
  index_buffer = std::make_shared<GLIndexBuffer>(indices, indices.size());
  vertex_array->AddVertexBuffer(vertex_buffer);
  vertex_array->SetIndexBuffer(index_buffer);
  vertex_array->Unbind();
}
void Mesh::Draw(const std::shared_ptr<GLShader> &shader) {
  uint diffuse_nr = 1;
  uint specular_nr = 1;
  uint normal_nr = 1;
  uint height_nr = 1;
  for (uint i = 0; i < textures_.size(); i++) {
    std::string name = textures_[i].type, number;
    if (name == "texture_diffuse") number = std::to_string(diffuse_nr++);
    else if (name == "texture_specular") number = std::to_string(specular_nr++);
    else if (name == "texture_normal") number = std::to_string(normal_nr++);
    else if (name == "texture_height") number = std::to_string(height_nr++);
    shader->UploadUniformInt(name+number, i);
    GLTexture::Bind(GL_TEXTURE0 + i, textures_[i].id);
  }
  vertex_array->Bind();
  RenderCommand::DrawIndex(vertex_array);
  vertex_array->Unbind();
  GLTexture::BindInitialize();
}

}