/*
 * Copyright (C) 2018-2019, neverfelly <neverfelly@gmail.com>
 *
 * This software is licensed under the terms of the MIT License.
 * See COPYING for further information.
 */
#pragma once

#include "shader.h"

MIN_NAMESPACE_BEGIN
namespace gl {

struct Vertex {
  Vector3 pos, normal;
  Vector2 text_coords;
  Vector3 tangent, bitangent;
};

struct Texture {
  unsigned int id;
  std::string type, path;
};

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

  void Draw(Shader shader) {
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
      glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
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
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, text_coords));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));
    glBindVertexArray(0);
  }
  unsigned VBO_, EBO_;
};

}
MIN_NAMESPACE_END


