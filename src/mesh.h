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
#include "gl_vertex_array.h"
#include "gl_shader.h"
#include "gl_texture.h"
#include "gl_render_command.h"

namespace min::engine {

struct Vertex {
  Vector3f position, normal;
  Vector2f tex_coords;
};

struct Texture {
  std::string path;
  std::string type;
};

class Mesh {
 public:
  Mesh(std::vector<Vertex> &vertices, std::vector<uint> &indices, std::vector<Texture> &textures, std::vector<GLTexture> &gl_textures);
  void Draw(const std::shared_ptr<GLShader> &shader);
 private:
  std::vector<Vertex> vertices_;
  std::vector<uint> indices_;
  std::vector<GLTexture> gl_textures_;
  std::vector<Texture> textures_;
  std::shared_ptr<GLVertexArray> vertex_array;
  std::shared_ptr<GLVertexBuffer> vertex_buffer;
  std::shared_ptr<GLIndexBuffer> index_buffer;
};

}