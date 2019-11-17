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

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "gl_shader.h"
#include "mesh.h"

namespace min::engine {

class Model {
 public:
  explicit Model(const std::string &path, bool gamma = false) : gamma_correction_(gamma) {
    LoadModel(path);
  }
  void Draw(const std::shared_ptr<GLShader>& shader) {
    for (auto & meshe : meshes_) {
      meshe.Draw(shader);
    }
  }
 private:
  void LoadModel(const std::string &path);

  void ProcessNode(aiNode *node, const aiScene *scene);

  Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);

  std::vector<Texture> LoadMaterialTextures(aiMaterial *material, aiTextureType type, std::string name);

  std::vector<Texture> textures_loaded_;
  std::vector<GLTexture> gl_textures_loaded_;
  std::vector<Mesh> meshes_;
  std::string dir_;
  bool gamma_correction_;
};

}
