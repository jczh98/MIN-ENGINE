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
  Vector3f tangent, bitangent;
};

struct Texture {
  uint id;
  std::string path;
  std::string type;
};
/**
class Mesh {
 public:
  Mesh(std::vector<Vertex> &vertices, std::vector<uint> &indices, std::vector<Texture> &textures);
  void Draw(const std::shared_ptr<GLShader> &shader);
 private:
  std::vector<Vertex> vertices_;
  std::vector<uint> indices_;
  std::vector<Texture> textures_;
  std::shared_ptr<GLVertexArray> vertex_array;
  std::shared_ptr<GLVertexBuffer> vertex_buffer;
  std::shared_ptr<GLIndexBuffer> index_buffer;
};
**/
class Mesh {
 public:
  Mesh(std::vector<Vertex> vertices,
       std::vector<unsigned int> indices,
       std::vector<Texture> textures)
      : vertices(vertices),
        indices(indices),
        textures(textures) {
    SetUpMesh();
  }

  void Draw(const std::shared_ptr<GLShader> shader) {
    uint diffuse_nr = 1;
    uint specular_nr = 1;
    uint normal_nr = 1;
    uint height_nr = 1;
    for (uint i = 0; i < textures.size(); i++) {
      glActiveTexture(GL_TEXTURE0 + i);
      std::string number, name = textures[i].type;
      if (name == "texture_diffuse") number = std::to_string(diffuse_nr++);
      else if (name == "texture_specular") number = std::to_string(specular_nr++);
      else if (name == "texture_normal") number = std::to_string(normal_nr++);
      else if (name == "texture_height") number = std::to_string(height_nr++);
      shader->UploadUniformInt(name+number, i);
      glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
  }
  unsigned int VAO;
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture> textures;
 private:
  void SetUpMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO_);
    glGenBuffers(1, &EBO_);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));
    glBindVertexArray(0);
  }
  unsigned VBO_, EBO_;
};

}
